#include <Commands/Ui/SaveCmd.hpp>

void SaveCmd::execute(const std::vector<std::string>& args)
{
	if (args.size() < 1)
	{
		throw GenericEvent::commandFail;
	}

	try {
		master.imgSave(args[0]);
	}
	catch (const std::exception& ex)
	{
		// add error to events
		master.getEvents().addEvent(GenericEvent::saveFail);
		return;
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(GenericEvent::saveSuccess);
}

std::string SaveCmd::getDisplayName()
{
	return displayName;
}

std::string SaveCmd::getShortName()
{
	return shortName;
}
