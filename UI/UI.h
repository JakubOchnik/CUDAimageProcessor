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

class Ui {
	bool quit = false;
	bool menu = true;
	bool loaded = false;

	std::vector<Event> eventQueue;

	std::string inputBuffer;

	MainHandler master = MainHandler();
	void helpScreen();
	void draw();
	void setWindowName(const std::string& newName) const;
	void clearScreen() const;

	void keystrokeHandler();
	std::string [[nodiscard]] printEvents() const;
	void clearEvents();
	void addEvent(Event& e);
	void editHistoryScreen();
	void showPreview(unsigned int scale = 0);
	std::tuple<int, int> customScale(cv::Mat& inputImage, unsigned int scale);
	std::tuple<int, int, float> autoScale(cv::Mat& inputImage, const std::tuple<int, int>& origSize, const std::tuple<int, int>& screenSize);
public:
	void uiHandler();
};