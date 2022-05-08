#pragma once
#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>

void executeInvertionKernel(Img& image, GPUcontroller* GPU);

__global__ void invertImage(unsigned char* image, int channels);
