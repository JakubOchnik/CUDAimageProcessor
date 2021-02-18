#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../MainHandler/definitions.h"
#include "../Utilities/GPUcontrol.h"
#include "brightnessKernel.h"
#include <sstream>
#include <algorithm>
class actionHandler {
private:
public:
	static event actionSelector(action name, Img* sourceImage, std::string value, GPUcontroller* GPUcontrol, bool forceUpdate = 0);
	static bool cropping(cv::Rect area, Img* srcImg);
	static bool resizing(unsigned int x, unsigned int y, Img* srcImg);
	static bool updateGPUmem(Img* srcImg, GPUcontroller* GPU, bool forceUpdate = 0);
	static bool isNumber(std::string value);
};
