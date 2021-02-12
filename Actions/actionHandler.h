#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../MainHandler/definitions.h"
#include "../Utilities/GPUcontrol.h"
#include "brightnessKernel.h"
class actionHandler {
private:
public:
	static event actionSelector(action name, Img* sourceImage, std::string value, GPUcontroller* GPUcontrol);
	static bool cropping(cv::Rect area, Img* srcImg);
	static bool updateGPUmem(Img* srcImg, GPUcontroller* GPU);
};
