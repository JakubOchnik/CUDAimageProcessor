#pragma once
#include <string>

enum class GenericEvent
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
