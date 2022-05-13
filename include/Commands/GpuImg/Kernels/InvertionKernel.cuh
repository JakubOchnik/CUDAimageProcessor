#pragma once
#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <memory>

void executeInvertionKernel(Img& image, const std::shared_ptr<GPUcontroller>& GPU);

__global__ void invertImage(unsigned char* image, int channels);
