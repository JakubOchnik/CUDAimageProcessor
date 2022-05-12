#pragma once
#include <string>

namespace event
{
enum class GenericProgramEvent
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
} // namespace event
