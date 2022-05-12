#pragma once
#include <Consts/Errors.hpp>
#include <Consts/GenericEvents.hpp>
#include <MainHandler/MainHandler.hpp>
class BaseCommand
{
protected:
	MainHandler& master;

public:
	BaseCommand(MainHandler& hdl);
	virtual std::string getShortName()	 = 0;
	virtual std::string getDisplayName() = 0;
};