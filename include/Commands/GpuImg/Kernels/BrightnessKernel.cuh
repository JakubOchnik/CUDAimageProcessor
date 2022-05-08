#include <cuda_runtime.h>
#include <Utilities/GPUcontrol.hpp>
#include <ImgHandling/ImgInfo.hpp>

void executeBrightnessKernel(Img& image, const int shift, GPUcontroller* GPU);

__global__ void calculateBrightness(unsigned char* image, int channels, int shift);
