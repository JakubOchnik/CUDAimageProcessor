#pragma once
#include <iostream>

enum action {
	crop,
	brightness,
	contrast,
	histogram,
	equalization,
	invertion,
	resize
};

// A struct which represents a specific edit (used in edit history)
struct edit {
	std::string value;
	action actionType;
};

enum event {
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
	GPUmallocFail
};