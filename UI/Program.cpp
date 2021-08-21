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
	// GET THE COMMAND NAME FROM THE INPUT STRING
	const auto command = inputBuffer.substr(0, inputBuffer.find(' '));
	// check if the command involves editing an image. If so, get img pointer and GPU handle
	std::set<std::string> val = { "quit", "load", "undo", "redo", "show", "help", "clear", "save", "history" };
	//Img* dstImg;
	//GPUcontroller* gpuControl;
	if (val.find(command) != val.end())
	{
		try {
			genericCmds.at(command)->execute();
		}
		catch (const std::exception& ex)
		{
			std::cout << "Error! " << ex.what() << "\n";
		}
	}
}
