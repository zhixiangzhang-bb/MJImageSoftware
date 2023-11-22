#include "Cuda.h"
#include "CUDARandom.cuh"
#include <iostream>



int main()
{
    int size = 1024;
    int bytes = size * sizeof(int);

    // 定义并分配主机内存
    int* h_a = new int[size];
    int* h_b = new int[size];
    int* h_c = new int[size];

    // 初始化数组
    for (int i = 0; i < size; i++) {
        h_a[i] = i;
        h_b[i] = i;
    }

    // 定义并分配设备内存
    int* d_a, * d_b, * d_c;
    cudaMalloc((void**)&d_a, bytes);
    cudaMalloc((void**)&d_b, bytes);
    cudaMalloc((void**)&d_c, bytes);

    // 将数据从主机内存复制到设备内存
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);

    // 定义网格和块的大小
    int blockSize = 256;
    int gridSize = (size + blockSize - 1) / blockSize;

    // 调用CUDA核函数
    addArrays << <gridSize, blockSize >> > (d_a, d_b, d_c, size);

    // 将结果从设备内存复制到主机内存
    cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost);

    // 打印结果
    for (int i = 0; i < size; i++) {
        std::cout << h_a[i] << " + " << h_b[i] << " = " << h_c[i] << std::endl;
    }

    // 释放内存
    delete[] h_a;
    delete[] h_b;
    delete[] h_c;
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    cudnntrain();
    return 0;
}


