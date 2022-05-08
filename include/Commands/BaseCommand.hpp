#pragma once
#include <Consts/Errors.hpp>
#include <MainHandler/MainHandler.hpp>
#include <MainHandler/definitions.hpp>
class BaseCommand
{
protected:
	MainHandler& master;

public:
	BaseCommand(MainHandler& hdl);
	virtual std::string getShortName()	 = 0;
	virtual std::string getDisplayName() = 0;
};