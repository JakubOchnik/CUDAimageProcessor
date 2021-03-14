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
	const std::string menuText = "CUDA IMAGE PROCESSOR\nJakub Ochnik 2021";
	const std::string infoResolution = "Image resolution:";
	const std::string infoChannels = "Image color channels:";
	const std::string pathText = "File path: ";
	const std::string prompt = "IP>";
	const std::string imgLoading = "Loading image, please wait...";
	const std::string notLoaded = "Image not loaded";
	const std::string textSeparator = "--------------------------------------------------";
	const std::string baseWindowName = "imgEditor";
	const std::string consoleName = baseWindowName;

	const std::vector<std::string> eventPrompts = {
		"File opened successfully",
		"File open failed. Check the path, extension or dimensions (they cannot exceed 65535x65535).",
		"File saved successfully",
		"File save failed",
		"Invalid command",
		"Action performed successfully",
		"Action failed",
		"Invalid action parameters",
		"Image has not been imported yet",
		"Can't undo - there are no performed operations yet",
		"Can't redo - there are no newer operations",
		"Cannot perform operation - insufficient video memory"
	};

	std::vector<int> eventQueue;

	const std::vector<std::string> actionNames = {
		"Image cropped: ",
		"Changed brightness: ",
		"Changed contrast: ",
		"Generated histogram",
		"Performed histogram equalization",
		"Inverted colors",
		"Resized image: "
	};

	const std::string helpText = "-- HELP --\n\nGENERAL FUNCTIONS:\n- quit - Exits the program\n- load [file_path] - Loads the image from the selected path\n- save [file_path] - Saves the edited image to the selected path\n- undo - Reverts the latest change\n- redo - Performs the latest reverted action\n- show [~scale] - Opens the image preview window. If the custom scale (in percentage, i.e. 75 % ->scale = 75) is not specified, the window will be automatically scaled to fit 80 % of main screen's vertical resolution.\n- history - Shows the history of changes\n- clear - Clears the notification area\n\nACTIONS:\n- brightness [value] - Changes brightness of the image by the specified value (it can be either negative or positive)\n- contrast [value] - Adjusts contrast (value must be in range <-255,255>)\n- invert - Inverts colors of the image\n- crop [x] [y] [width] [height] - Trims the image from the coordinates (x, y) to (x + width, y + height). Constraints: x + width < full width; y + height < full height.\n- resize [width] [height] - Resizes the image to the specified size\n- equalize - Performs histogram equalization\n\n(~- optional)";

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