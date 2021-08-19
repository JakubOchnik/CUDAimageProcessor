#pragma once
#include "../MainHandler/definitions.h"
#include "../MainHandler/MainHandler.h"
class BaseCommand
{
protected:
	MainHandler* handler = nullptr;
	bool initialized = false;
public:
	const std::string displayName = "base";
	BaseCommand();
	BaseCommand(MainHandler* handler);
	std::string getDisplayName() const;
};