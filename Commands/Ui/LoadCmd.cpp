#include "LoadCmd.hpp"

void LoadCmd::execute(const std::vector<std::string>& args)
{

	if (args.size() < 1)
	{
		throw Event::commandFail;
	}
	std::cout << FILE_LOADING_TEXT << '\n';
	try {
		master.updateSrcImg(args[0], 1);
	}
	catch (const std::exception& ex)
	{
		// add negative event to events
		master.getEvents().addEvent(Event::openFail);
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(Event::openSuccess);
}

std::string LoadCmd::getDisplayName()
{
	return displayName;
}

std::string LoadCmd::getShortName()
{
	return shortName;
}

