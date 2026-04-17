#!/bin/bash

# Default values if not provided via sbatch export
if [ -z "$NP" ]; then echo "Error: NP (total GPUs) not set"; exit 1; fi
if [ -z "$W" ]; then echo "Error: W (width) not set"; exit 1; fi
if [ -z "$H" ]; then echo "Error: H (height) not set"; exit 1; fi
if [ -z "$N" ]; then echo "Error: N (chares) not set"; exit 1; fi
if [ -z "$PPN" ]; then echo "Error: PPN (PEs per GPU) not set"; exit 1; fi
if [ -z "$ODF" ]; then ODF="unknown"; fi

RESULT_FILE="strong_scaling_results.csv"
NUM_RUNS=2

# Initialize result file header if it doesn't exist
if [ ! -f "$RESULT_FILE" ]; then
    echo "TotalGPUs,Nodes,Chares,ODF,PPN,Width,Height,TotalTime(s),TimePerIter(us)" > "$RESULT_FILE"
fi

echo "Starting $NUM_RUNS runs for: NP=$NP Nodes=$SLURM_NNODES W=$W H=$H N=$N PPN=$PPN"

# Variables to store the running totals
TOTAL_TIME_SUM=0
TIME_PER_ITER_SUM=0

# Environment setup
export LD_LIBRARY_PATH=/u/ajain18/reconverse_charm_integration/charm/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/u/ajain18/reconverse_charm_integration/lci_install/lib64:$LD_LIBRARY_PATH
export LCI_ATTR_BACKEND=ofi
export FI_CXI_RX_MATH_MODE=hybrid
export LCI_ATTR_BACKEND=ofi
export FI_CXI_RX_MATH_MODE=hybrid
export OFI_ROOT=/opt/cray/libfabric/1.15.2.0
export LCI_ROOT=/u/ajain18/reconverse_charm_integration/lci_install
export FI_MR_CACHE_MONITOR=userfaultfd
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/u/ajain18/hapi_hip/shogo/charm/kokkos/install/lib64
export PMI_MAX_KVS_ENTRIES=4096

for i in $(seq 1 $NUM_RUNS); do
    echo "--- Run $i of $NUM_RUNS ---"
    
    OUTPUT_LOG="run_${SLURM_JOB_ID}_${i}.log"
    
    srun --mpi=cray_shasta -n $NP build/jacobi2d.out +pe $((NP * PPN)) -z +gpushm +gpuipceventpool 32 +gpucommbuffer 1024 -W $W -H $H -N $N > "$OUTPUT_LOG"

    if [ $? -ne 0 ]; then
        echo "Error: srun failed on run $i"
        exit 1
    fi

    # Extract times using awk (handling the "no colon" format)
    T_TIME=$(awk '/Total time/ {print $3}' "$OUTPUT_LOG")
    I_TIME=$(awk '/Average iteration time/ {print $4}' "$OUTPUT_LOG")

    # Accumulate sums using 'bc' for floating point addition
    TOTAL_TIME_SUM=$(echo "$TOTAL_TIME_SUM + $T_TIME" | bc)
    TIME_PER_ITER_SUM=$(echo "$TIME_PER_ITER_SUM + $I_TIME" | bc)

    # Clean up individual log
    rm "$OUTPUT_LOG"
done

# Calculate averages using 'bc'
AVG_TOTAL_TIME=$(echo "scale=3; $TOTAL_TIME_SUM / $NUM_RUNS" | bc)
AVG_TIME_PER_ITER=$(echo "scale=3; $TIME_PER_ITER_SUM / $NUM_RUNS" | bc)

echo "Final Averages: Total=$AVG_TOTAL_TIME s, PerIter=$AVG_TIME_PER_ITER us"

# Append averages to CSV
echo "$NP,$SLURM_NNODES,$N,$ODF,$PPN,$W,$H,$AVG_TOTAL_TIME,$AVG_TIME_PER_ITER" >> "$RESULT_FILE"
