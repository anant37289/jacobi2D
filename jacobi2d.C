#include "hapi.h"
#include "jacobi2d.decl.h"
#include "jacobi2d.h"
#include <utility>
#include <sstream>
#include <Kokkos_Core.hpp>

#define COMM_ONLY 0
#define hapi_SYNC 0

using ExecSpace = Kokkos::DefaultExecutionSpace;
using RangePolicy = Kokkos::RangePolicy<ExecSpace>;
using MDRangePolicy = Kokkos::MDRangePolicy<Kokkos::Rank<2>, ExecSpace>;
using HostMemSpace = Kokkos::HostSpace;
#ifdef GPU_BACKEND
  #ifdef KOKKOS_ENABLE_CUDA
  using HostPinnedSpace = Kokkos::CudaHostPinnedSpace;
  #endif
  #ifdef KOKKOS_ENABLE_HIP
  using HostPinnedSpace = Kokkos::HIPHostPinnedSpace;
  #endif
#else
  using HostPinnedSpace = HostMemSpace;
#endif

/* readonly */ CProxy_Main main_proxy;
/* readonly */ CProxy_Block block_proxy;
/* readonly */ int grid_width;
/* readonly */ int grid_height;
// block_width and block_height are no longer global; computed per-chare
/* readonly */ int n_chares_x;
/* readonly */ int n_chares_y;
/* readonly */ int n_iters;
/* readonly */ int warmup_iters;
/* readonly */ bool sync_ver;
/* readonly */ bool use_zerocopy;
/* readonly */ bool print_elements;
/* readonly */ int lb_freq;
/* readonly */ int imbalance;
/* readonly */ CProxy_cuptiManager cupti_manager;
/* readonly */ int num_instrument_iter;
/* readonly */ bool use_lb;

enum Direction { LEFT = 1, RIGHT, TOP, BOTTOM };

class KokkosGroup : public CBase_KokkosGroup
{
public:
    KokkosGroup()
    {
        #ifdef GPU_BACKEND
        int device;
        hapiCheck(cudaGetDevice(&device));
        ckout<<"PE "<<CkMyPe()<< " using device "<<device<<endl;
        Kokkos::InitializationSettings args_kokkos;
        args_kokkos.set_device_id(device);
        Kokkos::initialize(args_kokkos);
        
        auto start = CkTimer();
        hapiCreateStreams();
        ckout << "Time to create streams " <<CkTimer() - start << endl;
        #endif
    }
};

class cuptiManager: public CBase_cuptiManager {
  public:
  cuptiManager(){}
  void Initialize() {
    hapiCuptiInit();
    CkCallback cb(CkReductionTarget(Main, cuptiInitialized), main_proxy);
    contribute(cb);
  }
  void Finalize() {
    hapiCuptiFinalize();
    CkCallback cb(CkReductionTarget(Main, cuptiFinalized), main_proxy);
    contribute(cb);
  }
};

CProxy_KokkosGroup kokkosMgmt;

class Main : public CBase_Main {
  int my_iter;
  double init_start_time;
  double start_time;
  double comm_start_time;
  double comm_agg_time;
  double update_start_time;
  double update_agg_time;
  double instrumented_iteration_start;
  double load_balance_start_time;
  double cupti_init_time_start;


public:
  Main(CkArgMsg* m) {
    // Set default values
    kokkosMgmt = CProxy_KokkosGroup::ckNew();
    main_proxy = thisProxy;
    grid_width = 16384;
    grid_height = 16384;
    n_iters = 100;
    warmup_iters = 10;
    use_zerocopy = false;
    print_elements = false;
    sync_ver = false;
    use_lb = false;
    my_iter = 0;
    lb_freq = 100;
    imbalance = 10;  // Max extra iterations for load imbalance
    num_instrument_iter = 0;
    cupti_manager = CProxy_cuptiManager::ckNew(); 

    // Initialize aggregate timers
    update_agg_time = 0.0;
    comm_agg_time = 0.0;

    // Process arguments
    int c;
    int target_num_chares = 4;

    while ((c = getopt(m->argc, m->argv, "W:H:i:u:N:yzpn:b:m:l")) != -1) {
      switch (c) {
        case 'W':
          grid_width = atoi(optarg);
          break;
        case 'H':
          grid_height = atoi(optarg);
          break;
        case 'i':
          n_iters = atoi(optarg);
          break;
        case 'u':
          warmup_iters = atoi(optarg);
          break;
        case 'N':
          target_num_chares = atoi(optarg);
          break;
        case 'y':
          sync_ver = true;
          break;
        case 'z':
          use_zerocopy = true;
          break;
        case 'p':
          print_elements = true;
          break;
        case 'n':
          num_instrument_iter = atoi(optarg);
          break;
        case 'b':
          lb_freq = atoi(optarg);
          break;
        case 'm':
          imbalance = atoi(optarg);
          break;
        case 'l':
          use_lb = true; 
          break;
        default:
          CkPrintf(
              "Usage: %s -W [grid width] -H [grid height] -N [num chares]"
              "-i [iterations] -u [warmup] -y (use sync version) -z (use GPU zerocopy) -p (print blocks)"
              "-n [num_instrument_iter] -b [lb_freq] -m [imbalance] -l (use_lb)\n",
              m->argv[0]);
          CkExit();
      }
    }
    delete m;

    n_chares_x = 1; 
    n_chares_y = target_num_chares;
    for (int i = static_cast<int>(sqrt(target_num_chares)); i >= 1; i--) {
      if (target_num_chares % i == 0) {
        n_chares_x = i;
        n_chares_y = target_num_chares / i;
        break;
      }
    }

    if (grid_width % n_chares_x != 0 || grid_height % n_chares_y != 0) {
        CkPrintf("Note: Grid not evenly divisible by chares. Using non-uniform decomposition.\n");
    }

    // Print configuration
    CkPrintf("\n[hapi 2D Jacobi example]\n");
    CkPrintf("Grid: %d x %d, Chares: %d x %d, Iterations: %d, "
        "Warm-up: %d, Bulk-synchronous: %d, Zerocopy: %d, Print: %d, lb_freq: %d, num_instrument_iter: %d\n\n",
        grid_width, grid_height, n_chares_x, n_chares_y,
        n_iters, warmup_iters, sync_ver, use_zerocopy, print_elements, lb_freq, num_instrument_iter);

    // Create blocks and start iteration
    block_proxy = CProxy_Block::ckNew(n_chares_x, n_chares_y);
    init_start_time = CkWallTimer();
    block_proxy.init();
  }

  void initDone() {
    CkPrintf("Init time: %.3lf s\n", CkWallTimer() - init_start_time);

    startIter();
  }

  void startIter() {
    if (my_iter++ == warmup_iters) start_time = CkWallTimer();
    update_start_time = CkWallTimer();

    block_proxy.exchangeGhosts();
  }

  void updateDone() {
    if (my_iter > warmup_iters) update_agg_time += CkWallTimer() - update_start_time;
    comm_start_time = CkWallTimer();

    block_proxy.packGhosts();
  }

  void commDone() {
    if (my_iter > warmup_iters) comm_agg_time += CkWallTimer() - comm_start_time;

    if (my_iter == warmup_iters + n_iters) {
      allDone();
    } else {
      startIter();
    }
  }

  void allDone() {
    double total_time = CkWallTimer() - start_time;
    CkPrintf("Total time: %.3lf s\nAverage iteration time: %.3lf s\n",
        total_time, (total_time / n_iters));
    if (sync_ver) {
      CkPrintf("Comm time per iteration: %.3lf s\nUpdate time per iteration: %.3lf s\n",
          (comm_agg_time / n_iters) , (update_agg_time / n_iters) );
    }

    if (print_elements) {
      sleep(1);
      block_proxy(0,0).print();
    } else {
      Kokkos::finalize();
      CkExit();
    }
  }

  void printDone() {
    Kokkos::finalize();
    CkExit();
  }

  void initializeCupti() {
    ckout<<"aggragatet time for this set of iteration -> (removed time for instrumented iterations and load balancing time) "<< (CkWallTimer() - start_time)/(lb_freq - num_instrument_iter) << " seconds"<<endl;
    cupti_init_time_start = CkWallTimer();
    cupti_manager.Initialize();
  }

  void cuptiInitialized()
  {
    double cupti_init_time = CkWallTimer() - cupti_init_time_start;
    ckout<<"time taken for CUPTI initialization: "<< cupti_init_time << " seconds"<<endl;
    instrumented_iteration_start = CkWallTimer();
    block_proxy.exchangeGhosts();
  }

  void finalizeCupti() {
    cupti_manager.Finalize();
  }

  void cuptiFinalized()
  {
    ckout<<"time taken for load balancing -> "<< (CkWallTimer() - load_balance_start_time) << " seconds"<<endl;
    block_proxy.exchangeGhosts();
    start_time = CkWallTimer();
  }

  void record_instrumented_iteration_times()
  {
    double instrumented_iteration_time = CkWallTimer() - instrumented_iteration_start;
    ckout<<"time for this set of instrumented iterations -> "<< instrumented_iteration_time/num_instrument_iter << " seconds"<<endl;
    block_proxy.callAtSync();
    load_balance_start_time = CkWallTimer();
  }
};

using DeviceMemSpace = ExecSpace::memory_space;

void invokeInitKernel(Kokkos::View<DataType*, DeviceMemSpace> d_temperature, int block_width, int block_height, ExecSpace exec_space) {
  Kokkos::deep_copy(exec_space, d_temperature,0);

  hapiCheck(hapiPeekAtLastError());
}

void invokeBoundaryKernels(Kokkos::View<DataType*, DeviceMemSpace> d_temperature, int block_width,
    int block_height, bool left_bound, bool right_bound, bool top_bound,
    bool bottom_bound, ExecSpace exec_space) {
  const int pitch = block_width + 2;
  if (left_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for("leftBoundaryKernel",RangePolicy(exec_space, 0, block_height), KOKKOS_LAMBDA(int i) { d_temperature(IDX(0, 1 + i, pitch)) = 1; }));
  }
  if (right_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "rightBoundaryKernel",
        RangePolicy(exec_space, 0, block_height), KOKKOS_LAMBDA(int i) { d_temperature(IDX(block_width + 1, 1 + i, pitch)) = 1; }));
  }

  if (top_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "topBoundaryKernel",
        RangePolicy(exec_space, 0, block_width), KOKKOS_LAMBDA(int i) { d_temperature(IDX(1 + i, 0, pitch)) = 1; }));
  }
  if (bottom_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "bottomBoundaryKernel",
        RangePolicy(exec_space, 0, block_width), KOKKOS_LAMBDA(int i) { d_temperature(IDX(1 + i, block_height + 1, pitch)) = 1; }));
  }
  hapiCheck(hapiPeekAtLastError());
}

void invokeJacobiKernel(Kokkos::View<DataType*, DeviceMemSpace> d_temperature, Kokkos::View<DataType*, DeviceMemSpace> d_new_temperature,
    int block_width, int block_height, int iters, ExecSpace exec_space) {
  const int pitch = block_width + 2;
  CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
      "invokeJacobiKernel",
      MDRangePolicy(exec_space,
          {1, 1}, {block_width + 1, block_height + 1}),
      KOKKOS_LAMBDA(int i, int j) {
        if(iters == 0) return;
        DataType value = 0;
        for(int iter = 0; iter < iters; iter++) {
            value += (d_temperature(IDX(i - 1, j, pitch)) + d_temperature(IDX(i + 1, j, pitch)) +
            d_temperature(IDX(i, j - 1, pitch)) + d_temperature(IDX(i, j + 1, pitch)) + d_temperature(IDX(i, j, pitch))) *
            0.2;
        }
        d_new_temperature(IDX(i, j, pitch)) = value/iters;
      }));
  
  hapiCheck(hapiPeekAtLastError());
}

void invokePackingKernels(Kokkos::View<DataType*, DeviceMemSpace> d_temperature, Kokkos::View<DataType*, 
                          DeviceMemSpace> d_left_ghost, Kokkos::View<DataType*, DeviceMemSpace> d_right_ghost, 
                          bool left_bound, bool right_bound, int block_width, int block_height, ExecSpace exec_space) {
  const int pitch = block_width + 2;
  if(!left_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "leftPackingKernel",
        RangePolicy(exec_space, 0, block_height),
        KOKKOS_LAMBDA(int j) {
          d_left_ghost(j) = d_temperature(IDX(1, 1 + j, pitch));
        }));
  }
  if(!right_bound) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "rightPackingKernel",
        RangePolicy(exec_space, 0, block_height),
        KOKKOS_LAMBDA(int j) {
          d_right_ghost(j) = d_temperature(IDX(block_width, 1 + j, pitch));
        }));
  }
  hapiCheck(hapiPeekAtLastError());
}

void invokeUnpackingKernel(Kokkos::View<DataType*, DeviceMemSpace> d_temperature, Kokkos::View<DataType*, DeviceMemSpace> d_ghost,
                           bool is_left, int block_width, int block_height, ExecSpace exec_space) {
  const int pitch = block_width + 2;
  if (is_left) {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "leftUnpackingKernel",
        RangePolicy(exec_space, 0, block_height),
        KOKKOS_LAMBDA(int j) {
          d_temperature(IDX(0, 1 + j, pitch)) = d_ghost(j);
        }));
  } else {
    CUPTI_LAUNCH_WRAPPER(Kokkos::parallel_for(
        "rightUnpackingKernel",
        RangePolicy(exec_space, 0, block_height),
        KOKKOS_LAMBDA(int j) {
          d_temperature(IDX(block_width + 1, 1 + j, pitch)) = d_ghost(j);
        }));
  }
  hapiCheck(hapiPeekAtLastError());
}

class Block : public CBase_Block {
  Block_SDAG_CODE

 public:
  int my_iter;
  int neighbors;
  int remote_count;
  int send_done_idx;
  int x, y;
  int block_width, block_height; // Local block dimensions
  double start_time;
  int load_iters;

  Kokkos::View<DataType*, HostPinnedSpace> h_temperature;
  Kokkos::View<DataType*, HostPinnedSpace> h_left_ghost;
  Kokkos::View<DataType*, HostPinnedSpace> h_right_ghost;
  Kokkos::View<DataType*, HostPinnedSpace> h_top_ghost;
  Kokkos::View<DataType*, HostPinnedSpace> h_bottom_ghost;

  Kokkos::View<DataType*, DeviceMemSpace> d_temperature;
  Kokkos::View<DataType*, DeviceMemSpace> d_new_temperature;
  Kokkos::View<DataType*, DeviceMemSpace> d_left_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_right_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_send_left_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_send_right_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_send_top_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_send_bottom_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_recv_left_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_recv_right_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_recv_top_ghost;
  Kokkos::View<DataType*, DeviceMemSpace> d_recv_bottom_ghost;

  hapiStream_t compute_stream;
  hapiStream_t comm_stream;

  ExecSpace comm_space;
  ExecSpace compute_space;

  hapiEvent_t compute_event;
  hapiEvent_t comm_event;

  bool left_bound, right_bound, top_bound, bottom_bound;

  Block() {
    usesAtSync = true;
  }

  Block(CkMigrateMessage* m)
  {
    ckout<<"["<<CkMyPe()<<"] block ("<<thisIndex.x<<","<<thisIndex.y<<") migrated"<<endl;

    usesAtSync = true;
    hapiCheck(hapiStreamCreateWithPriority(&compute_stream, hapiStreamDefault, 0));
    hapiCheck(hapiStreamCreateWithPriority(&comm_stream, hapiStreamDefault, -1));

    compute_space = ExecSpace(compute_stream); 
    comm_space = ExecSpace(comm_stream);

    hapiCheck(hapiEventCreateWithFlags(&compute_event, hapiEventDisableTiming));
    hapiCheck(hapiEventCreateWithFlags(&comm_event, hapiEventDisableTiming));

  }

  ~Block() {
    hapiCheck(hapiStreamDestroy(compute_stream));
    hapiCheck(hapiStreamDestroy(comm_stream));

    hapiCheck(hapiEventDestroy(compute_event));
    hapiCheck(hapiEventDestroy(comm_event));
  }

  void pup(PUP::er& p) {
    p | my_iter;
    p | neighbors;
    p | remote_count;
    p | x;
    p | y;
    p | block_width;
    p | block_height;
    p | left_bound;
    p | right_bound;
    p | top_bound;
    p | bottom_bound;
    p | load_iters;

    if(p.isUnpacking())
    {
      // h_temperature = Kokkos::View<DataType*, HostPinnedSpace>("h_temperature", (block_width + 2) * (block_height + 2));
      d_temperature = Kokkos::View<DataType*, DeviceMemSpace>("d_temperature", (block_width + 2) * (block_height + 2));
      d_new_temperature = Kokkos::View<DataType*, DeviceMemSpace>("d_new_temperature", (block_width + 2) * (block_height + 2));
      // h_left_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_left_ghost", block_height);
      // h_right_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_right_ghost", block_height);
      // h_top_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_top_ghost", block_width);
      // h_bottom_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_bottom_ghost", block_width);
      if (!use_zerocopy)
      {
        d_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_left_ghost", block_height);

        d_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_right_ghost", block_height);
      }
      else
      {
        d_send_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_left_ghost", block_height);

        d_send_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_right_ghost", block_height);

        d_send_top_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_top_ghost", block_width);

        d_send_bottom_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_bottom_ghost", block_width);

        d_recv_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_left_ghost", block_height);

        d_recv_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_right_ghost", block_height);

        d_recv_top_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_top_ghost", block_width);

        d_recv_bottom_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_bottom_ghost", block_width);
      }
    }
    p(d_temperature.data(), (block_width + 2) * (block_height + 2), PUP::PUPMode::DEVICE);
    p(d_new_temperature.data(), (block_width + 2) * (block_height + 2), PUP::PUPMode::DEVICE);
  }

  void init() {
    // Initialize values
    my_iter = 0;
    neighbors = 0;
    x = thisIndex.x;
    y = thisIndex.y;
    
    load_iters = 1 + (int)((((float) (x)) / (n_chares_x)) * imbalance);

    // ckout<<"["<<CkMyPe()<<"] block ("<<x<<","<<y<<") has load_iters: "<<load_iters<<endl;

    // Calculate local block dimensions with remainder distribution
    int base_w = grid_width / n_chares_x;
    int rem_w = grid_width % n_chares_x;
    block_width = base_w + (x < rem_w ? 1 : 0);

    int base_h = grid_height / n_chares_y;
    int rem_h = grid_height % n_chares_y;
    block_height = base_h + (y < rem_h ? 1 : 0);

    // Check bounds and set number of valid neighbors
    left_bound = right_bound = top_bound = bottom_bound = false;
    if (thisIndex.x == 0)
      left_bound = true;
    else
      neighbors++;
    if (thisIndex.x == n_chares_x - 1)
      right_bound = true;
    else
      neighbors++;
    if (thisIndex.y == 0)
      top_bound = true;
    else
      neighbors++;
    if (thisIndex.y == n_chares_y - 1)
      bottom_bound = true;
    else
      neighbors++;

    // h_temperature =
    //     Kokkos::View<DataType*, HostPinnedSpace>(
    //         "h_temperature",
    //         (block_width + 2) * (block_height + 2));

    // h_left_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_left_ghost", block_height);

    // h_right_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_right_ghost", block_height);

    // h_top_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_top_ghost", block_width);

    // h_bottom_ghost = Kokkos::View<DataType*, HostPinnedSpace>("h_bottom_ghost", block_width);


    // ---- Device allocations (GPU/ExecSpace device) ----
    d_temperature =
        Kokkos::View<DataType*, DeviceMemSpace>(
            "d_temperature",
            (block_width + 2) * (block_height + 2));

    d_new_temperature =
        Kokkos::View<DataType*, DeviceMemSpace>(
            "d_new_temperature",
            (block_width + 2) * (block_height + 2));


    // ---- Conditional ghost-layer allocations ----
    if (!use_zerocopy)
    {
        d_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_left_ghost", block_height);

        d_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_right_ghost", block_height);
    }
    else
    {
        d_send_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_left_ghost", block_height);

        d_send_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_right_ghost", block_height);

        d_send_top_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_top_ghost", block_width);

        d_send_bottom_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_send_bottom_ghost", block_width);

        d_recv_left_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_left_ghost", block_height);

        d_recv_right_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_right_ghost", block_height);

        d_recv_top_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_top_ghost", block_width);

        d_recv_bottom_ghost =
            Kokkos::View<DataType*, DeviceMemSpace>("d_recv_bottom_ghost", block_width);
    }

    hapiCheck(hapiStreamCreateWithPriority(&compute_stream, hapiStreamDefault, 0));
    hapiCheck(hapiStreamCreateWithPriority(&comm_stream, hapiStreamDefault, -1));

    compute_space = ExecSpace(compute_stream); 
    comm_space = ExecSpace(comm_stream);

    hapiCheck(hapiEventCreateWithFlags(&compute_event, hapiEventDisableTiming));
    hapiCheck(hapiEventCreateWithFlags(&comm_event, hapiEventDisableTiming));

    // Initialize temperature data
    invokeInitKernel(d_temperature, block_width, block_height, compute_space);
    invokeInitKernel(d_new_temperature, block_width, block_height, compute_space);

    // Enforce boundary conditions
    invokeBoundaryKernels(d_temperature, block_width, block_height, left_bound,
        right_bound, top_bound, bottom_bound, compute_space);
    invokeBoundaryKernels(d_new_temperature, block_width, block_height, left_bound,
        right_bound, top_bound, bottom_bound, compute_space);

#if hapi_SYNC
    hapiStreamSynchronize(compute_stream);
    thisProxy[thisIndex].initDone();
#else
    // TODO: Support reduction callback in hapiAddCallback
    CkCallback* cb = new CkCallback(CkIndex_Block::initDone(), thisProxy[thisIndex]);
    hapiAddCallback(compute_stream, cb);
#endif
  }

  void initDone() {
    contribute(CkCallback(CkReductionTarget(Main, initDone), main_proxy));
  }


  void iterate() {
    if (use_lb && my_iter != 0 && (my_iter+1) % lb_freq == 0) {
      cudaStreamSynchronize(comm_stream);
      cudaStreamSynchronize(compute_stream);

      CkCallback cb(CkReductionTarget(Main, record_instrumented_iteration_times), main_proxy);
      contribute(cb);
    } else {
      if(use_lb && (my_iter + num_instrument_iter + 1)%lb_freq==0) 
      { 
        CkCallback cb(CkReductionTarget(Main, initializeCupti), main_proxy);
        contribute(cb);
      }
      else 
      {
        thisProxy[thisIndex].exchangeGhosts();
      }
    }
  }

  void callAtSync()
  {
    AtSync();
  }

  void ResumeFromSync() {
    // ckout<<"object ("<<thisIndex.x<<", "<<thisIndex.y<<") resuming from sync"<<endl;
    CkCallback cb(CkReductionTarget(Main, finalizeCupti), main_proxy);
    contribute(cb);
  }

  void update() {
    // Operations in compute stream should only be executed when
    // operations in communication stream (transfers and unpacking) complete
    hapiCheck(hapiEventRecord(comm_event, comm_stream));
    hapiCheck(hapiStreamWaitEvent(compute_stream, comm_event, 0));

#if !COMM_ONLY
    // Invoke GPU kernel for Jacobi computation
    invokeJacobiKernel(d_temperature, d_new_temperature, block_width, block_height, load_iters, compute_space);
#endif

    // Operations in communication stream (packing and transfers) should
    // only be executed when operations in compute stream complete
    hapiCheck(hapiEventRecord(compute_event, compute_stream));
    hapiCheck(hapiStreamWaitEvent(comm_stream, compute_event, 0));

    if (sync_ver) {
#if hapi_SYNC
      hapiStreamSynchronize(compute_stream);
      thisProxy[thisIndex].updateDone();
#else
      CkCallback* cb = new CkCallback(CkIndex_Block::updateDone(), thisProxy[thisIndex]);
      hapiAddCallback(compute_stream, cb);
#endif
    }
  }

  void updateDone() {
    contribute(CkCallback(CkReductionTarget(Main, updateDone), main_proxy));
  }

  void packGhosts() {
    if (use_zerocopy) {
#if !COMM_ONLY
      // Pack non-contiguous ghosts to temporary contiguous buffers on device
      invokePackingKernels(d_new_temperature, d_send_left_ghost, d_send_right_ghost,
          left_bound, right_bound, block_width, block_height, comm_space);
#endif

      const size_t pitch = block_width + 2;

      if(!top_bound) {
        auto top_src = Kokkos::subview(d_new_temperature,
                                      std::make_pair(pitch + 1,
                                                      pitch + 1 + block_width));
        Kokkos::deep_copy(comm_space, d_send_top_ghost, top_src);
      }

      if (!bottom_bound) {
        auto bottom_src = Kokkos::subview(d_new_temperature,
                                        std::make_pair(pitch * block_height + 1,
                                                      pitch * block_height + 1 + block_width));
        Kokkos::deep_copy(comm_space, d_send_bottom_ghost, bottom_src);
      }
    } else {
#if !COMM_ONLY
      // Pack non-contiguous ghosts to temporary contiguous buffers on device
      invokePackingKernels(d_new_temperature, d_left_ghost, d_right_ghost,
          left_bound, right_bound, block_width, block_height, comm_space);
#endif

      size_t pitch = block_width + 2;

      // Device → Host: left ghost
      if (!left_bound) {
          Kokkos::deep_copy(comm_space, h_left_ghost, d_left_ghost);
      }

      // Device → Host: right ghost
      if (!right_bound) {
          Kokkos::deep_copy(comm_space, h_right_ghost, d_right_ghost);
      }

      // Device → Host: top ghost
      if (!top_bound) {
          auto top_src = Kokkos::subview(
              d_new_temperature,
              std::make_pair(pitch + 1,
                            pitch + 1 + block_width)
          );
          Kokkos::deep_copy(comm_space, h_top_ghost, top_src);
      }

      // Device → Host: bottom ghost
      if (!bottom_bound) {
          auto bottom_src = Kokkos::subview(
              d_new_temperature,
              std::make_pair(pitch * block_height + 1,
                            pitch * block_height + 1 + block_width)
          );
          Kokkos::deep_copy(comm_space, h_bottom_ghost, bottom_src);
      }
    }

#if hapi_SYNC
    hapiStreamSynchronize(comm_stream);
    thisProxy[thisIndex].packGhostsDone();
#else
    // Add asynchronous callback to be invoked when packing kernels and
    // ghost transfers are complete
    CkCallback* cb = new CkCallback(CkIndex_Block::packGhostsDone(), thisProxy[thisIndex]);
    hapiAddCallback(comm_stream, cb);
#endif
  }

  void sendGhosts() {
    // Send ghosts to neighboring chares
    if (use_zerocopy) {
      if (!left_bound) 
        thisProxy(x - 1, y).receiveGhostsZC(my_iter, RIGHT, block_height,
            CkDeviceBuffer(d_send_left_ghost.data(), CkCallback(CkIndex_Block::d_send_left_ghost_done(), thisProxy[thisIndex]), comm_stream));
      if (!right_bound)
        thisProxy(x + 1, y).receiveGhostsZC(my_iter, LEFT, block_height,
            CkDeviceBuffer(d_send_right_ghost.data(), CkCallback(CkIndex_Block::d_send_right_ghost_done(), thisProxy[thisIndex]), comm_stream));
      if (!top_bound)
        thisProxy(x, y - 1).receiveGhostsZC(my_iter, BOTTOM, block_width,
            CkDeviceBuffer(d_send_top_ghost.data(), CkCallback(CkIndex_Block::d_send_top_ghost_done(), thisProxy[thisIndex]), comm_stream));
      if (!bottom_bound)
        thisProxy(x, y + 1).receiveGhostsZC(my_iter, TOP, block_width,
            CkDeviceBuffer(d_send_bottom_ghost.data(), CkCallback(CkIndex_Block::d_send_bottom_ghost_done(), thisProxy[thisIndex]), comm_stream));
    } else {
      if (!left_bound)
        thisProxy(x - 1, y).receiveGhostsReg(my_iter, RIGHT, block_height, h_left_ghost.data());
      if (!right_bound)
        thisProxy(x + 1, y).receiveGhostsReg(my_iter, LEFT, block_height, h_right_ghost.data());
      if (!top_bound)
        thisProxy(x, y - 1).receiveGhostsReg(my_iter, BOTTOM, block_width, h_top_ghost.data());
      if (!bottom_bound)
        thisProxy(x, y + 1).receiveGhostsReg(my_iter, TOP, block_width, h_bottom_ghost.data());
    }
  }

  // This is the post entry method, the regular entry method is defined as a
  // SDAG entry method in the .ci file
  void receiveGhostsZC(int ref, int dir, int &size, DataType *&buf, CkDeviceBufferPost *devicePost) {
    switch (dir) {
      case LEFT:
        buf = d_recv_left_ghost.data();
        break;
      case RIGHT:
        buf = d_recv_right_ghost.data();
        break;
      case TOP:
        buf = d_recv_top_ghost.data();
        break;
      case BOTTOM:
        buf = d_recv_bottom_ghost.data();
        break;
      default:
        CkAbort("Error: invalid direction");
    }
    devicePost[0].hapi_stream = comm_stream;
  }

  void processGhostsZC(int dir, int size, DataType* gh) {
    switch (dir) {
      case LEFT:
        invokeUnpackingKernel(d_temperature, d_recv_left_ghost, true, block_width,
            block_height, comm_space);
        break;
      case RIGHT:
        invokeUnpackingKernel(d_temperature, d_recv_right_ghost, false, block_width,
            block_height, comm_space);
        break;
      case TOP: {
        auto dst = Kokkos::subview(d_temperature,
                                  std::make_pair((size_t)1, (size_t)(1 + block_width)));
        Kokkos::deep_copy(comm_space, dst, d_recv_top_ghost);
      } break;
      case BOTTOM: {
        size_t pitch = block_width + 2;
        size_t start = pitch * (block_height + 1) + 1;
        auto dst = Kokkos::subview(d_temperature,
                                  std::make_pair(start, start + (size_t)block_width));
        Kokkos::deep_copy(comm_space, dst, d_recv_bottom_ghost);
      } break;
      default:
        CkAbort("Error: invalid direction");
    }
  }

  void processGhostsReg(int dir, int size, DataType* gh) {
    switch (dir) {
      case LEFT: {
        memcpy(h_left_ghost.data(), gh, size * sizeof(DataType));
        Kokkos::deep_copy(comm_space, d_left_ghost, h_left_ghost);
#if !COMM_ONLY
        invokeUnpackingKernel(d_temperature, d_left_ghost, true, block_width,
            block_height, comm_space);
#endif
        thisProxy[thisIndex].d_send_left_ghost_done();
      } break;
      case RIGHT: {
        memcpy(h_right_ghost.data(), gh, size * sizeof(DataType));
        Kokkos::deep_copy(comm_space, d_right_ghost, h_right_ghost);
#if !COMM_ONLY
        invokeUnpackingKernel(d_temperature, d_right_ghost, false, block_width,
            block_height, comm_space);
#endif
        thisProxy[thisIndex].d_send_right_ghost_done();
      } break;
      case TOP: {
        memcpy(h_top_ghost.data(), gh, size * sizeof(DataType));
          auto dst = Kokkos::subview(
              d_temperature,
              std::make_pair(1, 1 + block_width)   // d_temperature + 1
          );

          Kokkos::deep_copy(comm_space, dst, h_top_ghost);
          thisProxy[thisIndex].d_send_top_ghost_done();
      } break;
      case BOTTOM: {
        memcpy(h_bottom_ghost.data(), gh, size * sizeof(DataType));
        size_t pitch = block_width + 2;
        size_t start = pitch * (block_height + 1) + 1;

        auto dst = Kokkos::subview(
            d_temperature,
            std::make_pair(start, start + block_width)
        );

        Kokkos::deep_copy(comm_space, dst, h_bottom_ghost);
        thisProxy[thisIndex].d_send_bottom_ghost_done();
      } break;
      default:
        CkAbort("Error: invalid direction");
    }
  }

  void copyToHost() {
    hapiCheck(hapiStreamSynchronize(comm_stream));
    hapiCheck(hapiStreamSynchronize(compute_stream));
    h_temperature = Kokkos::View<DataType*, HostPinnedSpace>("h_temperature", (block_width + 2) * (block_height + 2));
    Kokkos::deep_copy(h_temperature, d_temperature);
  }

  void print() {
    copyToHost();
    CkPrintf("[%d,%d]\n", thisIndex.x, thisIndex.y);
    for (int j = 0; j < block_height + 2; j++) {
      for (int i = 0; i < block_width + 2; i++) {
#ifdef TEST_CORRECTNESS
        CkPrintf("%d ", h_temperature[(block_width + 2) * j + i]);
#else
        CkPrintf("%.6lf ", h_temperature[(block_width + 2) * j + i]);
#endif
      }
      CkPrintf("\n");
    }

    if (!(thisIndex.x == n_chares_x-1 && thisIndex.y == n_chares_y-1)) {
      if (thisIndex.x == n_chares_x-1) {
        thisProxy(0,thisIndex.y+1).print();
      } else {
        thisProxy(thisIndex.x+1,thisIndex.y).print();
      }
    } else {
      main_proxy.printDone();
    }
  }
};

#include "jacobi2d.def.h"
