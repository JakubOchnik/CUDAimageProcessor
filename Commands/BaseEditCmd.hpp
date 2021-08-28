#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
#include "../CodeUtils/utils.hpp"
class BaseEditCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};