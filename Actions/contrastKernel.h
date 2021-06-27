#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void executeContrastKernel(Img* image, int value, GPUcontroller* GPU);
__global__ void calculateContrast(unsigned char* image, int channels, float factor);
__device__ unsigned char truncate(float value);
