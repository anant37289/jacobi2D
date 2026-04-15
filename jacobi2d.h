#ifndef __CUDA_GPUDIRECT_JACOBI2D_H_
#define __CUDA_GPUDIRECT_JACOBI2D_H_

#ifdef TEST_CORRECTNESS
typedef int DataType;
#else
typedef float DataType;
#endif

#define IDX(x,y,pitch) ((pitch)*(y)+(x))

#endif // __CUDA_GPUDIRECT_JACOBI2D_H_
