#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <iostream>
#include <cudnn.h>




__global__
void addArrays(int* a, int* b, int* c, int size);	



