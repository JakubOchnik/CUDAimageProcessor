#include "Program.hpp"

ProgramHandler::ProgramHandler()
{
	genericCmds.emplace(UndoCmd::shortName, std::make_shared<UndoCmd>(master));
	genericCmds.emplace(ShowCmd::shortName, std::make_shared<ShowCmd>(master));
	genericCmds.emplace(SaveCmd::shortName, std::make_shared<SaveCmd>(master));
	genericCmds.emplace(RedoCmd::shortName, std::make_shared<RedoCmd>(master));
	genericCmds.emplace(QuitCmd::shortName, std::make_shared<QuitCmd>(master));
	genericCmds.emplace(LoadCmd::shortName, std::make_shared<LoadCmd>(master));
	genericCmds.emplace(HistoryCmd::shortName, std::make_shared<HistoryCmd>(master));
	genericCmds.emplace(HelpCmd::shortName, std::make_shared<HelpCmd>(master));
	genericCmds.emplace(ClearCmd::shortName, std::make_shared<ClearCmd>(master));
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
	using EditMapType = std::unordered_map<std::string, std::shared_ptr<BaseGenericCmd>>;


	const auto genericNames = Utils::keys<GenericMapType>(genericCmds);
	const auto EditNames = Utils::keys<EditMapType>(genericCmds);


	// GET THE COMMAND NAME FROM THE INPUT STRING
	std::string processedCmd;
	std::vector<std::string> processedArgs;
	try
	{
		const auto processedInput = TextUtils::processArgs(inputBuffer);
		processedCmd = processedInput.first;
		processedArgs = processedInput.second;
	}
	catch (const std::exception& ex)
	{
		master.getEvents().addEvent(Event::commandFail);
		return;
	}

	if (find(genericNames.begin(), genericNames.end(), processedCmd) != genericNames.end())
	{
		// Execute generic command group
		try {
			genericCmds.at(processedCmd)->execute(processedArgs);
		}
		catch (const std::exception& ex)
		{
			master.getEvents().addEvent(Event::commandFail);
			std::cerr << "Error! " << ex.what() << "\n";
		}
	}
}
