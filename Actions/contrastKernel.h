#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"

void executeContrastKernel(Img *image, int value, GPUcontroller *GPU);