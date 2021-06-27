#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void executeBrightnessKernel(Img* image, int shift, GPUcontroller* GPU);
__global__ void calculateBrightness(unsigned char* image, int channels, int shift);
