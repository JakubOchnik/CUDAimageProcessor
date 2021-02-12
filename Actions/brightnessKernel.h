#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"

void executeBrightnessKernel(Img* image, int shift, GPUcontroller* GPU);