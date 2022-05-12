#include <Commands/Ui/SaveCmd.hpp>

void SaveCmd::execute(const std::vector<std::string>& args)
{
	using namespace event;
	if (args.size() < 1)
	{
		throw GenericProgramEvent::commandFail;
	}

	try
	{
		master.imgSave(args[0]);
	}
	catch (const std::exception& ex)
	{
		// add error to events
		master.getEvents().addEvent(GenericProgramEvent::saveFail);
		return;
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(GenericProgramEvent::saveSuccess);
}

std::string SaveCmd::getDisplayName()
{
	return displayName;
}

std::string SaveCmd::getShortName()
{
	return shortName;
}
