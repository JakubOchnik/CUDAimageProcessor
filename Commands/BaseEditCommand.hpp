#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseEditCommand : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	virtual void execute(const std::vector<std::string>& args, MainHandler& master) = 0;

};