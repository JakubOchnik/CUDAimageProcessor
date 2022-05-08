#pragma once
#include <Commands/BaseCommand.hpp>
#include <MainHandler/MainHandler.hpp>
class BaseGenericCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;

public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};