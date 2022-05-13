#pragma once
#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <memory>

#ifdef __INTELLISENSE__
#define atomicAdd();
#define atomicMin();
#define atomicMax();
#endif

bool executeEqualizationKernel(Img& image, const std::shared_ptr<GPUcontroller>& GPU);

__global__ void calculateEdgeBrightness(unsigned char* image, int channels, int* min, int* max);

__global__ void calculateEqualization(unsigned char* image, int channels, int* min, int* max);

__device__ int getEqualizedValue(unsigned char value, int min, int max);
