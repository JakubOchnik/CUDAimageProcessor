#pragma once
#include <CodeUtils/utils.hpp>
#include <Commands/AllEditCmds.hpp>
#include <Commands/BaseCommand.hpp>
#include <Commands/BaseEditCmd.hpp>
#include <Commands/BaseGenericCmd.hpp>
#include <Commands/Ui/AllCommands.hpp>
#include <Consts/Consts.hpp>
#include <Consts/Errors.hpp>
#include <Consts/GenericEvents.hpp>
#include <MainHandler/MainHandler.hpp>
#include <UI/UIdefinitions.hpp>
#include <UI/ui.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <exception>
#include <memory>
#include <string>

class ProgramHandler
{
	MainHandler master;
	std::string inputBuffer;

	std::unordered_map<std::string, std::shared_ptr<BaseGenericCmd>> genericCmds;
	std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>>	 editCmds;

	// if mode == gpu
	// std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>> gpuEditCmds;
	// if mode == cpu
	// std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>> CpuEditCmds;

	void initializeCommands();

	void keystrokeHandler();
	void undoAction();
	void redoAction();

	template <typename T>
	void executeCommand(std::shared_ptr<T>&				cmd,
						const std::vector<std::string>& processedArgs)
	{
		try
		{
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