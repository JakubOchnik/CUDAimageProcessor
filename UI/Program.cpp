#include "Program.hpp"

ProgramHandler::ProgramHandler()
{
	genericCmds.emplace(ShowCmd::shortName, std::make_shared<ShowCmd>(master));
	genericCmds.emplace(SaveCmd::shortName, std::make_shared<SaveCmd>(master));
	genericCmds.emplace(QuitCmd::shortName, std::make_shared<QuitCmd>(master));
	genericCmds.emplace(LoadCmd::shortName, std::make_shared<LoadCmd>(master));
	genericCmds.emplace(HistoryCmd::shortName, std::make_shared<HistoryCmd>(master));
	genericCmds.emplace(HelpCmd::shortName, std::make_shared<HelpCmd>(master));
	genericCmds.emplace(ClearCmd::shortName, std::make_shared<ClearCmd>(master));

	editCmds.emplace(CropCmd::shortName, std::make_shared<CropCmd>(master));
}

void ProgramHandler::run()
{
	ui::setWindowName(BASE_WINDOW_NAME);
	// Main loop
	while (!master.isQuit())
	{
		ui::draw(master.getDstImg(), master.getEvents(), master.isLoaded());
		std::getline(std::cin, inputBuffer);
		keystrokeHandler();
	}
}

void ProgramHandler::keystrokeHandler()
{
	using namespace std;
	using GenericMapType = std::unordered_map<std::string, std::shared_ptr<BaseGenericCmd>>;
	using EditMapType = std::unordered_map<std::string, std::shared_ptr<BaseEditCmd>>;


	const auto genericNames = Utils::keys<GenericMapType>(genericCmds);
	const auto editNames = Utils::keys<EditMapType>(editCmds);


	// GET THE COMMAND NAME FROM THE INPUT STRING
	std::string processedCmd;
	std::vector<std::string> processedArgs;
	try
	{
		const auto processedInput = TextUtils::processArgs(inputBuffer);
		processedCmd = processedInput.first;
		processedArgs = processedInput.second;
	}
	catch (const std::runtime_error& ex)
	{
		master.getEvents().addEvent(ex);
		return;
	}

	if (find(genericNames.begin(), genericNames.end(), processedCmd) != genericNames.end()
		)
	{
		std::shared_ptr<BaseGenericCmd> cmd = genericCmds.at(processedCmd);
		// Execute generic command group
		executeCommand<BaseGenericCmd>(cmd, processedArgs);
	}
	else if (find(editNames.begin(), editNames.end(), processedCmd) != editNames.end())
	{
		std::shared_ptr<BaseEditCmd> cmd = editCmds.at(processedCmd);
		// Execute generic command group
		executeCommand<BaseEditCmd>(cmd, processedArgs);
		master.getHistory().addToHistory(cmd->getShortName(), cmd->getDisplayName(), processedArgs);
	}
	else if (processedCmd == consts::cmd::REDO_CMD)
	{
		// Dispatch undo/redo commands
		// They cannot be implemented as regular commands in order to avoid circular dependency
		master.getHistory().actionRedo();
	}
	else if (processedCmd == consts::cmd::UNDO_CMD)
	{
		try
		{
			undoAction();
		}
		catch (const std::runtime_error& ex)
		{
			master.getEvents().addEvent(ex);
			//std::cerr << "Error! " << ex.what() << "\n";
		}
	}
	else
	{
		master.getEvents().addEvent(GenericEvent::commandFail);
	}
}


void ProgramHandler::undoAction()
{
	//Img newImg;
	//newImg = master.getSrcImg();
	master.updateDstImg(master.getSrcImg());
	// perform all of the operations on source image besides from the latest one
	auto& history = master.getHistory();
	if (history.size() > 1)
	{
		size_t i{ 0 };
		for (const Edit& edit : history.getHistory())
		{

			std::shared_ptr<BaseEditCmd> cmd = editCmds.at(edit.shortName);
			// Execute edit command group
			executeCommand<BaseEditCmd>(cmd, edit.args);

			i++;
			if (i >= history.size() - 1)
			{
				break;
			}
		}
	}
	else if (history.getHistory().empty())
	{
		throw std::runtime_error("History is empty.");//Event::undoFail;
	}

	//master.getDstImg() = newImg;
	history.actionUndo();

	/*
	if (!ActionHandler::updateGPUmem(&dstImg, &GPUControl, true))
	{
		throw Event::GPUmallocFail;
	}
	*/
}
