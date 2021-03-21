#pragma once

#include "../ImgHandling/ImgInfo.h"
#include "../MainHandler/MainHandler.h"
#include "../MainHandler/definitions.h"
#include "../Actions/ActionHandler.h"
#include "UIdefinitions.h"

#include <stdlib.h>
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

class UI
{
private:
	bool quit;
	bool menu;
	bool loaded;

	std::vector<int> eventQueue;

	std::string inputBuffer;

	MainHandler master;
	void helpScreen();
	void draw();
	bool keystrokeHandler();
	const std::string printEvents() const;
	void clearEvents();
	void editHistoryScreen();
	bool showPreview(unsigned int scale = 0);

public:
	UI();
	void UIHandler();
	~UI();
};