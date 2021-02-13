#pragma once
#include <stdlib.h>
#include<iostream>
#include<string>
#include"../ImgHandling/ImgInfo.h"
#include"../MainHandler/mainHandler.h"
#include"../MainHandler/definitions.h"
#include "../Actions/actionHandler.h"
#include<vector>
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

	std::vector<std::string> eventPrompts = {
		"File opened successfully",
		"File open failed. Check the path, extension or dimensions (they can't exceed 65535).",
		"File saved successfully",
		"File save failed",
		"Invalid command",
		"Action performed successfully",
		"Action failed",
		"Invalid action parameters"
	};

	std::vector<int> eventQueue;

	std::vector<std::string> actionNames = {
		"Image cropped: ",
		"Changed brightness: ",
		"Changed contrast: ",
		"Generated histogram",
		"Performed histogram equalization",
		"Inverted colors"
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
	~UI();
};