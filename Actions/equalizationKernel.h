#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"

bool executeEqualizationKernel(Img *image, GPUcontroller *GPU);