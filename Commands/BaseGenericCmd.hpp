#pragma once
#include "BaseCommand.hpp"
#include "../MainHandler/MainHandler.h"
class BaseGenericCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	static inline const std::string displayName = "BaseGenericCommand";
	static inline const std::string shortName = "generic";
	virtual void execute(const std::string& args = "") = 0;
};