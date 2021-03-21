#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"

void executeInvertionKernel(Img *image, GPUcontroller *GPU);
