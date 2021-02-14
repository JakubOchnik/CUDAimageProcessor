#pragma once
#include <stdlib.h>
#include<iostream>
#include<string>
#include"../ImgHandling/ImgInfo.h"
#include"../MainHandler/mainHandler.h"
#include"../MainHandler/definitions.h"
#include "../Actions/actionHandler.h"
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
	std::string menuText;
	std::string infoResolution;
	std::string infoChannels;
	std::string pathText;
	std::string prompt;
	std::string notLoaded;
	std::string textSeparator;
	std::string previewWindowName;

	std::vector<std::string> eventPrompts = {
		"File opened successfully",
		"File open failed. Check the path, extension or dimensions (they can't exceed 65535).",
		"File saved successfully",
		"File save failed",
		"Invalid command",
		"Action performed successfully",
		"Action failed",
		"Invalid action parameters",
		"Image has not been imported yet"
	};

	std::vector<int> eventQueue;

	std::vector<std::string> actionNames = {
		"Image cropped: ",
		"Changed brightness: ",
		"Changed contrast: ",
		"Generated histogram",
		"Performed histogram equalization",
		"Inverted colors",
		"Resized image: "
	};

	std::string inputBuffer;

	mainHandler master;
public:
	UI();
	void UIHandler();
	bool keystrokeHandler();
	void draw();
	std::string printEvents();
	void clearEvents();
	void editHistoryScreen();
	bool showPreview(unsigned int scale=0);
	~UI();
};