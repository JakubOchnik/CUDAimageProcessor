#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#ifdef __INTELLISENSE__
#define atomicAdd();
#define atomicMin();
#define atomicMax();
#endif

bool executeEqualizationKernel(Img* image, GPUcontroller* GPU);
__global__ void calculateEdgeBrightness(unsigned char* image, int channels, int* min, int* max);
__global__ void calculateEqualization(unsigned char* image, int channels, int* min, int* max);
__device__ int getEqualizedValue(unsigned char value, int min, int max);