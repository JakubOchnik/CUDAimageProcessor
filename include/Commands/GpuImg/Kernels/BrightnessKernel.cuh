#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <memory>

void executeBrightnessKernel(Img& image, const int shift, const std::shared_ptr<GPUcontroller>& GPU);

__global__ void calculateBrightness(unsigned char* image, int channels, int shift);
