#pragma once
#include "../UI/ui.h"
#include "../Commands/BaseCommand.hpp"
#include "../Commands/BaseGenericCmd.hpp"
#include "../MainHandler/MainHandler.h"

class ProgramHandler
{
	MainHandler master;
	std::string inputBuffer;

	std::set<std::string> nonEditCmds = { "quit", "load", "undo", "redo", "show", "clear", "save", "history" };
	//std::vector<BaseCommand> tx = { LoadCmd() };
	std::vector<BaseGenericCmd> genericCmds = {};
	void keystrokeHandler(MainHandler& master);
public:
	void run();
};