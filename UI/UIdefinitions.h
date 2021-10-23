#pragma once

#include <string>
#include <map>

const std::string HEADER_TEXT = "CUDA IMAGE PROCESSOR\nJakub Ochnik 2021";
const std::string RESOLUTION_TEXT = "Image resolution:";
const std::string CHANNELS_TEXT = "Image color channels:";
const std::string FILEPATH_TEXT = "File path: ";
const std::string PROMPT_TEXT = "IP>";
const std::string FILE_LOADING_TEXT = "Loading image, please wait...";
const std::string NOT_LOADED_TEXT = "Image not loaded";
const std::string SEPARATOR_TEXT = "--------------------------------------------------";
const std::string BASE_WINDOW_NAME = "imgEditor";
const std::string CONSOLE_NAME = BASE_WINDOW_NAME;

const std::map<GenericEvent, std::string> EVENT_TEXT_PROMPTS = {
	{GenericEvent::openSuccess, "File opened successfully"},
	{GenericEvent::openFail, "File open failed. Check the path, extension or dimensions (they cannot exceed 65535x65535)."},
	{GenericEvent::saveSuccess, "File saved successfully"},
	{GenericEvent::saveFail, "File save failed"},
	{GenericEvent::commandFail, "Invalid command"},
	{GenericEvent::actionSuccess, "Action performed successfully"},
	{GenericEvent::actionFail, "Action failed"},
	{GenericEvent::parameterFail, "Invalid action parameters"},
	{GenericEvent::noImage, "Image has not been imported yet"},
	{GenericEvent::undoFail, "Can't undo - there are no performed operations yet"},
	{GenericEvent::redoFail, "Can't redo - there are no newer operations"},
	{GenericEvent::GPUmallocFail, "Cannot perform operation - insufficient video memory"},
};

const std::string HELP_TEXT_CONTENT =
"-- HELP --\n\nGENERAL FUNCTIONS:\n- quit - Exits the program\n- load [file_path] - Loads the image from the selected path\n- save [file_path] - Saves the edited image to the selected path\n- undo - Reverts the latest change\n- redo - Performs the latest reverted action\n- show [~scale] - Opens the image preview window. If the custom scale (in percentage, i.e. 75 % ->scale = 75) is not specified, the window will be automatically scaled to fit 80 % of main screen's vertical resolution.\n- history - Shows the history of changes\n- clear - Clears the notification area\n\nACTIONS:\n- brightness [value] - Changes brightness of the image by the specified value (it can be either negative or positive)\n- contrast [value] - Adjusts contrast (value must be in range <-255,255>)\n- invert - Inverts colors of the image\n- crop [x] [y] [width] [height] - Trims the image from the coordinates (x, y) to (x + width, y + height). Constraints: x + width < full width; y + height < full height.\n- resize [width] [height] - Resizes the image to the specified size\n- equalize - Performs histogram equalization\n\n(~- optional)";
