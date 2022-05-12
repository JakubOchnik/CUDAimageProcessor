#pragma once

#include <map>
namespace consts
{
namespace ui
{

constexpr const char* const HEADER_TEXT =
	"CUDA IMAGE PROCESSOR\nJakub Ochnik 2021";
constexpr const char* const RESOLUTION_TEXT	  = "Image resolution:";
constexpr const char* const CHANNELS_TEXT	  = "Image color channels:";
constexpr const char* const FILEPATH_TEXT	  = "File path: ";
constexpr const char* const PROMPT_TEXT		  = "IP>";
constexpr const char* const FILE_LOADING_TEXT = "Loading image, please wait...";
constexpr const char* const NOT_LOADED_TEXT	  = "Image not loaded";
constexpr const char* const SEPARATOR_TEXT =
	"--------------------------------------------------";
constexpr const char* const BASE_WINDOW_NAME = "imgEditor";
constexpr const char* const CONSOLE_NAME	 = "imgEditor";

const std::map<GenericProgramEvent, const char*> EVENT_TEXT_PROMPTS = {
	{GenericProgramEvent::openSuccess, "File opened successfully"},
	{GenericProgramEvent::openFail,
	 "File open failed. Check the path, extension or dimensions (they cannot "
	 "exceed 65535x65535)."},
	{GenericProgramEvent::saveSuccess, "File saved successfully"},
	{GenericProgramEvent::saveFail, "File save failed"},
	{GenericProgramEvent::commandFail, "Invalid command"},
	{GenericProgramEvent::actionSuccess, "Action performed successfully"},
	{GenericProgramEvent::actionFail, "Action failed"},
	{GenericProgramEvent::parameterFail, "Invalid action parameters"},
	{GenericProgramEvent::noImage, "Image has not been imported yet"},
	{GenericProgramEvent::undoFail,
	 "Can't undo - there are no performed operations yet"},
	{GenericProgramEvent::redoFail,
	 "Can't redo - there are no newer operations"},
	{GenericProgramEvent::GPUmallocFail,
	 "Cannot perform operation - insufficient video memory"},
};

constexpr const char* const HELP_TEXT_CONTENT =
	"-- HELP --\n\nGENERAL FUNCTIONS:\n- quit - Exits the program\n- load "
	"[file_path] - Loads the image from the selected path\n- save [file_path] "
	"- Saves the edited image to the selected path\n- undo - Reverts the "
	"latest change\n- redo - Performs the latest reverted action\n- show "
	"[~scale] - Opens the image preview window. If the custom scale (in "
	"percentage, i.e. 75 % ->scale = 75) is not specified, the window will be "
	"automatically scaled to fit 80 % of main screen's vertical resolution.\n- "
	"history - Shows the history of changes\n- clear - Clears the notification "
	"area\n\nACTIONS:\n- brightness [value] - Changes brightness of the image "
	"by the specified value (it can be either negative or positive)\n- "
	"contrast [value] - Adjusts contrast (value must be in range "
	"<-255,255>)\n- invert - Inverts colors of the image\n- crop [x] [y] "
	"[width] [height] - Trims the image from the coordinates (x, y) to (x + "
	"width, y + height). Constraints: x + width < full width; y + height < "
	"full height.\n- resize [width] [height] - Resizes the image to the "
	"specified size\n- equalize - Performs histogram equalization\n\n(~- "
	"optional)";
} // namespace ui
} // namespace consts