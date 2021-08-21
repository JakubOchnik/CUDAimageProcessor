#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseEditCommand : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	static inline const std::string displayName = "BaseEditCommand";
	static inline const std::string shortName = "edit";
	virtual void execute(const std::string& args, MainHandler& master);
};