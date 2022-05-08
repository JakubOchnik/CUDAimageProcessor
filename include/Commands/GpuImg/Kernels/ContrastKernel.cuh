#pragma once
#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>

void executeContrastKernel(Img& image, int value, GPUcontroller* GPU);
__global__ void calculateContrast(unsigned char* image, int channels, float factor);
__device__ unsigned char truncate(float value);
