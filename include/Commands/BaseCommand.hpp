#pragma once
#include <MainHandler/definitions.hpp>
#include <MainHandler/MainHandler.hpp>
#include <Consts/Errors.hpp>
class BaseCommand
{
protected:
	MainHandler& master;
public:
	BaseCommand(MainHandler& hdl);
	virtual std::string getShortName() = 0;
	virtual std::string getDisplayName() = 0;
};