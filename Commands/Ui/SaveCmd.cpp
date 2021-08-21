#include "SaveCmd.hpp"

void SaveCmd::execute(const std::string& args)
{
	if (args.length() < 2)
	{
		throw Event::commandFail;
	}
	if (master.imgSave(args))
	{
		master.getEvents().addEvent(Event::saveSuccess);
	}
	else
	{
		throw Event::saveFail;
	}
}

std::string SaveCmd::getDisplayName()
{
	return displayName;
}

std::string SaveCmd::getShortName()
{
	return shortName;
}
