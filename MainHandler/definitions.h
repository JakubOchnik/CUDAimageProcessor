#pragma once
#include <iostream>
enum action {
	crop,
	brightness,
	contrast,
	histogram,
	equalization,
	invertion
};
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
	parameterFail
};