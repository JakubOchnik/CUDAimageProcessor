#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

void executeInvertionKernel(Img* image, GPUcontroller* GPU);
__global__ void invertImage(unsigned char* image, int channels);
