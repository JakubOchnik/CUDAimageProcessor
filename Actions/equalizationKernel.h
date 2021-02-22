#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../Utilities/GPUcontrol.h"

void executeEqualizationKernel(Img* image, GPUcontroller* GPU);