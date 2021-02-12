#include "actionHandler.h"
#include "brightnessKernel.h"
#include<algorithm>

bool actionHandler::updateGPUmem(Img* srcImg, GPUcontroller* GPU) {
	if (!GPU->getGPUmemStatus()) {
		GPU->GPUmalloc(srcImg);
	}
	else if(GPU->sizeUpdateStatus()) {
		GPU->updatePtr(srcImg);
	}
	return 1;
}

bool actionHandler::cropping(cv::Rect area, Img* srcImg) {
	cv::Mat newImg(*srcImg->getImg());
	newImg = newImg(area);
	srcImg->updateAll(newImg);
	return true;
}

event actionHandler::actionSelector(action name, Img* sourceName, std::string value, GPUcontroller* GPUcontrol) {
	if (name == crop) {
		// x y width height
		try {
			int x1 = value.find(' ');
			int x2 = value.find(' ', x1 + 1);
			int x3 = value.find(' ', x2 + 1);
			if (x1 <= 0 || x1 == x2 || x2 <= 0 || x2 == x3 || x3 <= 0) {
				throw parameterFail;
			}
			int x = stoi((value.substr(0, x1)));
			int y = stoi((value.substr(x1, x2)));
			int w = stoi((value.substr(x2, x3)));
			int h = stoi((value.substr(x3, value.length() - 1)));
			if (x < 0 || y < 0 || w <= 0 || h <= 0) {
				throw parameterFail;
			}
			if (x + w > sourceName->getResolutionW() || y + h > sourceName->getResolutionH()) {
				throw parameterFail;
			}
			// zlec wykonanie funkcji
			if (!cropping(cv::Rect(x, y, w, h), sourceName)) {
				throw actionFail;
			}
		}
		catch (event e) {
			return e;
		}
		return actionSuccess;
	}
	else if (name == brightness) {
		try {
			int shift = 0;
			if (value[0] == '-') {
				
				shift = stoi(value.substr(1, value.length() - 1));
				shift *= (-1);
			}
			else {
				shift = stoi(value.substr(0, value.length()));
			}
			updateGPUmem(sourceName, GPUcontrol);
			executeBrightnessKernel(sourceName, shift,GPUcontrol);
			return actionSuccess;
		}
		catch (event e)
		{
			return e;
		}
	}
	return commandFail;
}
