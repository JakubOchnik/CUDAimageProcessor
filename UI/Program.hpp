#pragma once
#include "../UI/ui.h"
#include "../Commands/BaseCommand.hpp"
#include "../Commands/BaseGenericCmd.hpp"
#include "../MainHandler/MainHandler.h"
#include "../Commands/Ui/AllCommands.hpp"
#include <string>
#include <exception>
#include <memory>

class ProgramHandler
{
	MainHandler master;
	std::string inputBuffer;

	std::unordered_map<std::string, std::shared_ptr<BaseGenericCmd>> genericCmds;
	/*
	std::unordered_map<std::string, std::unique_ptr<BaseGenericCmd>> genericCmds =
	{
		{UndoCmd::shortName, std::make_shared<UndoCmd>(master)},
		{ShowCmd::shortName, std::make_shared<ShowCmd>(master)},
		{SaveCmd::shortName, std::make_shared<SaveCmd>(master)},
		{RedoCmd::shortName, std::make_shared<RedoCmd>(master)},
		{QuitCmd::shortName, std::make_shared<QuitCmd>(master)},
		{LoadCmd::shortName, std::make_shared<LoadCmd>(master)},
		{HistoryCmd::shortName, std::make_shared<HistoryCmd>(master)},
		{HelpCmd::shortName, std::make_shared<HelpCmd>(master)},
		{ClearCmd::shortName, std::make_shared<ClearCmd>(master)}
	};
	*/
	void keystrokeHandler();
public:
	ProgramHandler();
	void run();
};