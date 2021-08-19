#pragma once

#include"../ImgHandling/ImgInfo.h"
#include"../MainHandler/MainHandler.h"
#include"../MainHandler/definitions.h"
#include "../Actions/ActionHandler.h"
#include "UIdefinitions.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

namespace ui
{
	void clearScreen();
	std::tuple<int, int> customScale(cv::Mat& inputImage, Img& dstImg, unsigned int scale);
	std::tuple<int, int, float> autoScale(cv::Mat& inputImage, Img& dstImg, const std::tuple<int, int>& origSize,
		const std::tuple<int, int>& screenSize);
	void editHistoryScreen(const History& history);
	void showPreview(Img& dstImg, unsigned int scale = 0);
	void helpScreen();
	void draw(const Img& dstImg, const EventHistory& events, bool loaded);
	void setWindowName(const std::string& newName);
	void printString(const std::string& output);
};
