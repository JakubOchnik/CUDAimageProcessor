#include "SaveCmd.hpp"

void SaveCmd::execute(MainHandler& master, const std::string& args)
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
