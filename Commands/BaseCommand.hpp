#pragma once
#include "../MainHandler/definitions.h"
#include "../MainHandler/MainHandler.h"
#include "../MainHandler/Errors.hpp"
class BaseCommand
{
protected:
	MainHandler& master;
public:
	BaseCommand(MainHandler& hdl);
	virtual std::string getShortName() = 0;
	virtual std::string getDisplayName() = 0;
};