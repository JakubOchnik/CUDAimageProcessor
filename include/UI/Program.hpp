#pragma once
#include <UI/ui.hpp>
#include <MainHandler/definitions.hpp>
#include <UI/UIdefinitions.hpp>
#include <Commands/BaseCommand.hpp>
#include <Commands/BaseGenericCmd.hpp>
#include <Commands/BaseEditCmd.hpp>
#include <MainHandler/MainHandler.hpp>
#include <Commands/Ui/AllCommands.hpp>
#include <Commands/AllEditCmds.hpp>
#include <CodeUtils/utils.hpp>
#include <Consts/Errors.hpp>
#include <Consts/Consts.hpp>
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

	// if mode == gpu
	// std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>> gpuEditCmds;
	// if mode == cpu
	// std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>> CpuEditCmds;

	void initializeCommands();

	void keystrokeHandler();
	void undoAction();
	void redoAction();

	template<typename T>
	void executeCommand(std::shared_ptr<T>& cmd, const std::vector<std::string>& processedArgs)
	{
		try {
			cmd->execute(processedArgs);
		}
		catch (const std::runtime_error& ex)
		{
			master.getEvents().addEvent(ex);
		}
	}
public:
	ProgramHandler(bool gpu);
	void run();
};