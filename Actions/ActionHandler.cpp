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
	const std::string::iterator end_pos = std::remove(value.begin(), value.end(), ' ');
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
	if (number == 0 && value[0] != '0') {
		return false;
	}
	return true;
}

std::vector<int> ActionHandler::parseLineParams(const unsigned int nParams, const std::string& line)
{
	std::vector<int> params;
	int prevX{ 0 };
	int x{ 1 };
	for (unsigned int i{ 0 }; i < nParams - 1; ++i)
	{
		x = line.find(' ', prevX + 1);
		if (x == std::string::npos || x <= 0 || x == prevX || !isNumber(line.substr(prevX, x - prevX)))
		{
			throw Event::parameterFail;
		}
		params.emplace_back(stoi(line.substr(prevX, x - prevX)));
		prevX = x;
	}
	// last parameter
	if (!isNumber(line.substr(x, line.length() - 1)))
	{
		throw Event::parameterFail;
	}
	params.emplace_back(stoi(line.substr(x)));
	return params;
}

Event ActionHandler::actionSelector(Action name, Img* sourceName, std::string value, GPUcontroller* GPUcontrol, bool forceUpdate) {
	if (!sourceName->getStatus()) {
		throw Event::noImage;
	}
	try {
		int x1, x2, x3, x, y, w, h, contr, shift;
		std::vector<int> params;
		switch (name) {
		case Action::crop:
			params = parseLineParams(4, value);
			// getting all the parameters
			x1 = value.find(' ');
			x2 = value.find(' ', x1 + 1);
			x3 = value.find(' ', x2 + 1);
			// error checking
			if (x1 == std::string::npos || x2 == std::string::npos || x3 == std::string::npos || x1 <= 0 || x1 == x2 || x2 <= 0 || x2 == x3 || x3 <= 0) {
				throw Event::parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, x2)) || !isNumber(value.substr(x2, x3)) || !isNumber(value.substr(x3, value.length() - 1))) {
				// check if all parameters are numbers
				throw Event::parameterFail;
			}
			// extract the parameters from string
			x = stoi((value.substr(0, x1)));
			y = stoi((value.substr(x1, x2)));
			w = stoi((value.substr(x2, x3)));
			h = stoi((value.substr(x3, value.length() - 1)));
			if (x < 0 || y < 0 || w <= 0 || h <= 0) {
				throw Event::parameterFail;
			}
			if (x + w > sourceName->getResolutionW() || y + h > sourceName->getResolutionH()) {
				throw Event::parameterFail;
			}
			// execute the action
			if (!cropping(cv::Rect(x, y, w, h), sourceName)) {
				throw Event::actionFail;
			}
			return Event::actionSuccess;
		case Action::resize:
			x1 = value.find(' ');
			if (x1 == std::string::npos || x1 <= 0 || x1 == value.length()) {
				throw Event::parameterFail;
			}
			if (!isNumber(value.substr(0, x1)) || !isNumber(value.substr(x1, value.length()))) {
				// check if all parameters are numbers
				throw Event::parameterFail;
			}
			x = stoi((value.substr(0, x1)));
			y = stoi((value.substr(x1, value.length())));
			if (x <= 0 || y <= 0) {
				throw Event::parameterFail;
			}
			// zlec wykonanie funkcji
			if (!resizing(x, y, sourceName)) {
				throw Event::actionFail;
			}
			return Event::actionSuccess;
		case Action::brightness:
			shift = 0;
			if (!isNumber(value)) {
				// check if parameter is a number
				throw Event::parameterFail;
			}
			if (value[0] == '-') {

				shift = stoi(value.substr(1, value.length() - 1));
				shift *= (-1);
			}
			else {
				shift = stoi(value.substr(0, value.length()));
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeBrightnessKernel(sourceName, shift, GPUcontrol);
			return Event::actionSuccess;
		case Action::invertion:
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeInvertionKernel(sourceName, GPUcontrol);
			return Event::actionSuccess;
		case Action::equalization:
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			if (!executeEqualizationKernel(sourceName, GPUcontrol)) {
				return Event::actionFail;
			}
			return Event::actionSuccess;
		case Action::contrast:
			contr = 0;
			if (!isNumber(value)) {
				// check if parameter is a number
				throw Event::parameterFail;
			}
			if (value[0] == '-') {

				contr = stoi(value.substr(1, value.length() - 1));
				contr *= (-1);
			}
			else {
				contr = stoi(value.substr(0, value.length()));
			}
			if (contr < -255 || contr >255) {
				throw Event::parameterFail;
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeContrastKernel(sourceName, contr, GPUcontrol);
			return Event::actionSuccess;
		case Action::lut3d:
			applyLUT(sourceName, 1.0f, "M31 - Rec.709.cube", GPUcontrol);
			return Event::actionSuccess;
		default:
			return Event::commandFail;
		}
	}
	catch (Event e) {
		return e;
	}
}
