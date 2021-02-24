#pragma once
#include <iostream>
const enum action {
	crop,
	brightness,
	contrast,
	histogram,
	equalization,
	invertion,
	resize
};
struct edit {
	std::string value;
	action actionType;
};

const enum event {
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
	redoFail
};