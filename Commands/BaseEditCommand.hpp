#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseEditCommand : public BaseCommand
{
	const std::string displayName = "edit";
public:
	virtual void execute(const std::string& args, MainHandler& master);
};