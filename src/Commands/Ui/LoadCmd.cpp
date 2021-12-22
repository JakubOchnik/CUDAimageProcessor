#include <Commands/Ui/LoadCmd.hpp>

void LoadCmd::execute(const std::vector<std::string>& args)
{

	if (args.empty())
	{
		throw std::exception("Command failed");
	}
	std::cout << FILE_LOADING_TEXT << '\n';
	try {
		master.updateDstImg(args[0], 1);
	}
	catch (const std::exception&)
	{
		// add negative event to events
		master.getEvents().addEvent(GenericEvent::openFail);
		return;
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(GenericEvent::openSuccess);
}

std::string LoadCmd::getDisplayName()
{
	return displayName;
}

std::string LoadCmd::getShortName()
{
	return shortName;
}

