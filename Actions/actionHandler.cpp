#include "actionHandler.h"

bool actionHandler::updateGPUmem(Img* srcImg, GPUcontroller* GPU, bool forceUpdate) {
	if (!GPU->getGPUmemStatus()) {
		if (!GPU->GPUmalloc(srcImg)) {
			return false;
		};
	} else if (forceUpdate || GPU->sizeUpdateStatus()){
		GPU->updatePtr(srcImg);
	}
	return true;
}

bool actionHandler::cropping(cv::Rect area, Img* srcImg) {
	cv::Mat newImg(*srcImg->getImg());
	newImg = newImg(area);
	srcImg->updateAll(newImg);
	return true;
}

bool actionHandler::resizing(unsigned int x, unsigned int y, Img* srcImg) {
	cv::Mat newImg(*srcImg->getImg());
	cv::resize(*srcImg->getImg(), newImg, cv::Size(x, y));
	srcImg->updateAll(newImg);
	return true;
}

bool actionHandler::isNumber(std::string value) {
	std::string::iterator end_pos = std::remove(value.begin(), value.end(), ' ');
	value.erase(end_pos, value.end());
	if (value.empty())
		return false;
	std::stringstream ss;
	ss << value;
	int number;
	ss >> number;
	if (ss.good()) {
		return false;
	}
	else if (number == 0 && value[0] != '0') {
		return false;
	}
	else {
		return true;
	}
	return true;
}


event actionHandler::actionSelector(action name, Img* sourceName, std::string value, GPUcontroller* GPUcontrol, bool forceUpdate) {
	if (name == crop) {
		// PARAMETERS: x y width height
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			// getting all the parameters
			int x1 = value.find(' ');
			int x2 = value.find(' ', x1 + 1);
			int x3 = value.find(' ', x2 + 1);
			// error checking
			if (x1 == std::string::npos || x2 == std::string::npos || x3 == std::string::npos || x1 <= 0 || x1 == x2 || x2 <= 0 || x2 == x3 || x3 <= 0) {
				throw parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, x2)) || !isNumber(value.substr(x2, x3)) || !isNumber(value.substr(x3, value.length() - 1))) {
				// check if all parameters are numbers
				throw parameterFail;
			}
			// extract the parameters from string
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
			// execute the action
			if (!cropping(cv::Rect(x, y, w, h), sourceName)) {
				throw actionFail;
			}
		}
		catch (event e) {
			return e;
		}
		return actionSuccess;
	} else if (name == resize) {
		// parameters: width height
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			int x1 = value.find(' ');
			if (x1==std::string::npos || x1 <= 0 || x1 == value.length()) {
				throw parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, value.length()))) {
				// check if all parameters are numbers
				throw parameterFail;
			}
			unsigned int x = stoi((value.substr(0, x1)));
			unsigned int y = stoi((value.substr(x1, value.length())));
			if (x <= 0 || y <= 0) {
				throw parameterFail;
			}
			// zlec wykonanie funkcji
			if (!resizing(x,y,sourceName)) {
				throw actionFail;
			}
		}
		catch (event e) {
			return e;
		}
		return actionSuccess;
	} else if (name == brightness) {
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			int shift = 0;
			if (!isNumber(value)) {
				// check if parameter is a number
				throw parameterFail;
			}
			if (value[0] == '-') {
				
				shift = stoi(value.substr(1, value.length() - 1));
				shift *= (-1);
			}
			else {
				shift = stoi(value.substr(0, value.length()));
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			executeBrightnessKernel(sourceName, shift,GPUcontrol);
			return actionSuccess;
		}
		catch (event e)
		{
			return e;
		}
	}
	else if (name == invertion) {
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			executeInvertionKernel(sourceName, GPUcontrol);
			return actionSuccess;
		}
		catch (event e)
		{
			return e;
		}
	}
	else if (name == equalization) {
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			if (!executeEqualizationKernel(sourceName, GPUcontrol)) {
				return actionFail;
			}
			return actionSuccess;
		}
		catch (event e) {
			return e;
		}
	}
	else if (name == contrast) {
		try {
			if (!sourceName->getStatus()) {
				throw noImage;
			}
			int contr = 0;
			if (!isNumber(value)) {
				// check if parameter is a number
				throw parameterFail;
			}
			if (value[0] == '-') {

				contr = stoi(value.substr(1, value.length() - 1));
				contr *= (-1);
			}
			else {
				contr = stoi(value.substr(0, value.length()));
			}
			if (contr < -255 || contr >255) {
				throw parameterFail;
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			executeContrastKernel(sourceName, contr, GPUcontrol);
			return actionSuccess;
		}
		catch (event e) {
			return e;
		}
	}
	return commandFail;
}
