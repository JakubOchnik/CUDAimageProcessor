#pragma once
#include <string>

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
