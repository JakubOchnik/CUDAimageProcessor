#pragma once
#include <CodeUtils/utils.hpp>
#include <Commands/BaseCommand.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <MainHandler/MainHandler.hpp>

class BaseEditCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;

public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};
