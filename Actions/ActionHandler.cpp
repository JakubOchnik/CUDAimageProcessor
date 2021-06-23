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
	if (nParams == 1)
	{
		if (!isNumber(line))
		{
			throw Event::parameterFail;
		}
		return std::vector<int>{stoi(line)};
	}
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
		if (name == Action::crop)
		{
			std::vector<int> params = parseLineParams(4, value);
			const int x{ params[0] }, y{ params[1] }, w{ params[2] }, h{ params[3] };
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
		}
		else if (name == Action::resize)
		{
			std::vector<int> params = parseLineParams(2, value);
			const int x{ params[0] }, y{ params[1] };
			if (x <= 0 || y <= 0) {
				throw Event::parameterFail;
			}
			// execute
			if (!resizing(x, y, sourceName)) {
				throw Event::actionFail;
			}
		}
		else if (name == Action::brightness)
		{
			const int shift = parseLineParams(1, value)[0];
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeBrightnessKernel(sourceName, shift, GPUcontrol);
		}
		else if (name == Action::invertion)
		{
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeInvertionKernel(sourceName, GPUcontrol);
		}
		else if (name == Action::equalization)
		{
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			if (!executeEqualizationKernel(sourceName, GPUcontrol)) {
				return Event::actionFail;
			}
		}
		else if (name == Action::contrast)
		{
			const int contrast = parseLineParams(1, value)[0];
			if (contrast < -255 || contrast >255) {
				throw Event::parameterFail;
			}
			if (!updateGPUmem(sourceName, GPUcontrol, forceUpdate)) {
				throw Event::GPUmallocFail;
			};
			executeContrastKernel(sourceName, contrast, GPUcontrol);
		}
		else if (name == Action::lut3d)
		{
			applyLUT(sourceName, 1.0f, "M31 - Rec.709.cube", GPUcontrol);
		}
		else
		{
			throw Event::commandFail;
		}
	}
	catch (const Event& e) {
		return e;
	}
	return Event::actionSuccess;
}
