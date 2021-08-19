#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseGenericCmd : public BaseCommand
{
	const std::string displayName = "generic";
public:
	virtual void execute(MainHandler& master, const std::string& args = "");
};