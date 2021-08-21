#pragma once
#include "../MainHandler/definitions.h"
#include "../MainHandler/MainHandler.h"
class BaseCommand
{
protected:
	MainHandler& master;
public:
	static inline const std::string displayName = "BaseCommand";
	static inline const std::string shortName = "base";
	BaseCommand(MainHandler& hdl);
};