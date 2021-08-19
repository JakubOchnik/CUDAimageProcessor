#pragma once
#include <string>

enum class Action
{
	crop,
	brightness,
	contrast,
	histogram,
	equalization,
	invertion,
	resize,
	lut3d
};

// A struct which represents a specific edit (used in edit history)
struct Edit
{
	std::string value;
	Action actionType;
};

enum class Event
{
	openSuccess,
	openFail,
	saveSuccess,
	saveFail,
	commandFail,
	actionSuccess,
	actionFail,
	parameterFail,
	noImage,
	undoFail,
	redoFail,
	GPUmallocFail,
	notImplemented
};
