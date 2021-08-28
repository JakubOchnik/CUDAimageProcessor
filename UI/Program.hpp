#pragma once
#include "../UI/ui.h"
#include "../Commands/BaseCommand.hpp"
#include "../Commands/BaseGenericCmd.hpp"
#include "../Commands/BaseEditCmd.hpp"
#include "../MainHandler/MainHandler.h"
#include "../Commands/Ui/AllCommands.hpp"
#include "../Commands/AllEditCmds.hpp"
#include "../CodeUtils/utils.hpp"
#include <string>
#include <exception>
#include <memory>
#include <boost/algorithm/string/trim.hpp>

class ProgramHandler
{
	MainHandler master;
	std::string inputBuffer;

	std::unordered_map<std::string, std::shared_ptr<BaseGenericCmd>> genericCmds;
	std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>> editCmds;
	void keystrokeHandler();
public:
	ProgramHandler();
	void run();
};