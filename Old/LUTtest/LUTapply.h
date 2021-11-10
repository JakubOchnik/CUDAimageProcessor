#pragma once
#include "../../ImgHandling/ImgInfo.h"
#include "../../Utilities/GPUcontrol.h"
#include <string>

void applyLUT(Img* image, float opacity, std::string path, GPUcontroller* GPU);