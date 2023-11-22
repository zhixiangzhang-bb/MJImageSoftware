#include "CUDARandom.cuh"





// CUDA核函数：将两个数组相加
__global__ void addArrays(int* a, int* b, int* c, int size)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < size) {
        c[i] = a[i] + b[i];
    }
}


