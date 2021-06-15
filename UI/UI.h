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

class UI {
private:
	bool quit;
	bool menu;
	bool loaded;

	std::vector<int> eventQueue;

	std::string inputBuffer;

	MainHandler master;
	void helpScreen();
	void draw();
	void keystrokeHandler();
	std::string printEvents() const;
	void clearEvents();
	void editHistoryScreen();
	void showPreview(unsigned int scale = 0);
	std::tuple<int, int> customScale(cv::Mat& inputImage, unsigned int scale);
	std::tuple<int, int, float> UI::autoScale(cv::Mat& inputImage, const std::tuple<int, int>& origSize, const std::tuple<int, int>& screenSize);
public:
	UI();
	void uiHandler();
	~UI();
};