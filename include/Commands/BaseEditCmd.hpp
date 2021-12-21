#pragma once
#include <Commands/BaseCommand.hpp>
#include <MainHandler/MainHandler.hpp>
#include <CodeUtils/utils.hpp>
#include <ImgHandling/ImgInfo.hpp>

class BaseEditCmd : public BaseCommand
{
	using BaseCommand::BaseCommand;
public:
	virtual void execute(const std::vector<std::string>& args) = 0;
};