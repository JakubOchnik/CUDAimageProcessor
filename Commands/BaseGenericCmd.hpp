#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseGenericCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};