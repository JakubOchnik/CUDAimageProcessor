#include "SaveCmd.hpp"

void SaveCmd::execute(const std::vector<std::string>& args)
{
	if (args.size() < 1)
	{
		throw Event::commandFail;
	}

	try {
		master.imgSave(args[0]);
	}
	catch (const std::exception& ex)
	{
		// add negative event to events
		master.getEvents().addEvent(Event::saveFail);
		return;
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(Event::saveSuccess);
}

std::string SaveCmd::getDisplayName()
{
	return displayName;
}

std::string SaveCmd::getShortName()
{
	return shortName;
}
