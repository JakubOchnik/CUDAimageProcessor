#pragma once
#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <memory>

void executeContrastKernel(Img& image, int value, const std::shared_ptr<GPUcontroller>& GPU);

__global__ void calculateContrast(unsigned char* image, int channels, float factor);

__device__ unsigned char truncate(float value);
