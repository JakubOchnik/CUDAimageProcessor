#include "ActionHandler.h"

bool ActionHandler::updateGPUmem(Img* srcImg, GPUcontroller* GPU, bool forceUpdate) {
	if (!GPU->getGPUmemStatus()) {
		if (!GPU->GPUmalloc(srcImg)) {
			return false;
		};
	}
	else if (forceUpdate || GPU->sizeUpdateStatus()) {
		GPU->updatePtr(srcImg);
	}
	return true;
}

bool ActionHandler::cropping(cv::Rect area, Img* srcImg) {
	cv::Mat newImg(*srcImg->getImg());
	newImg = newImg(area);
	srcImg->updateAll(newImg);
	return true;
}

bool ActionHandler::resizing(unsigned int x, unsigned int y, Img* srcImg) {
	cv::Mat newImg(*srcImg->getImg());
	cv::resize(*srcImg->getImg(), newImg, cv::Size(x, y));
	srcImg->updateAll(newImg);
	return true;
}

bool ActionHandler::isNumber(std::string value) {
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
	return true;
}

// TODO: MOVE THE PARAMETER PARSER TO ANOTHER FUNCTION
event ActionHandler::actionSelector(action name, Img* sourceName, std::string value, GPUcontroller* GPUcontrol, bool forceUpdate) {
	if (!sourceName->getStatus()) {
		throw noImage;
	}
	try {
		int x1, x2, x3, x, y, w, h, contr, shift;
		switch (name) {
		case crop:
			// getting all the parameters
			x1 = value.find(' ');
			x2 = value.find(' ', x1 + 1);
			x3 = value.find(' ', x2 + 1);
			// error checking
			if (x1 == std::string::npos || x2 == std::string::npos || x3 == std::string::npos || x1 <= 0 || x1 == x2 || x2 <= 0 || x2 == x3 || x3 <= 0) {
				throw parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, x2)) || !isNumber(value.substr(x2, x3)) || !isNumber(value.substr(x3, value.length() - 1))) {
				// check if all parameters are numbers
				throw parameterFail;
			}
			// extract the parameters from string
			x = stoi((value.substr(0, x1)));
			y = stoi((value.substr(x1, x2)));
			w = stoi((value.substr(x2, x3)));
			h = stoi((value.substr(x3, value.length() - 1)));
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
			return actionSuccess;
			break;
		case resize:
			x1 = value.find(' ');
			if (x1 == std::string::npos || x1 <= 0 || x1 == value.length()) {
				throw parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, value.length()))) {
				// check if all parameters are numbers
				throw parameterFail;
			}
			x = stoi((value.substr(0, x1)));
			y = stoi((value.substr(x1, value.length())));
			if (x <= 0 || y <= 0) {
				throw parameterFail;
			}
			// zlec wykonanie funkcji
			if (!resizing(x, y, sourceName)) {
				throw actionFail;
			}
			return actionSuccess;
			break;
		case brightness:
			shift = 0;
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
			executeBrightnessKernel(sourceName, shift, GPUcontrol);
			return actionSuccess;
			break;
		case invertion:
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			executeInvertionKernel(sourceName, GPUcontrol);
			return actionSuccess;
			break;
		case equalization:
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw GPUmallocFail;
			};
			if (!executeEqualizationKernel(sourceName, GPUcontrol)) {
				return actionFail;
			}
			return actionSuccess;
			break;
		case contrast:
			contr = 0;
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
			break;
		case lut3d:
			applyLUT(sourceName, 1.0f, "M31 - Rec.709.cube", GPUcontrol);
			break;
		default:
			return commandFail;
			break;

		}
	}
	catch (event e) {
		return e;
	}
	return commandFail;
}
