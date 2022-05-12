#include <Commands/Ui/LoadCmd.hpp>

void LoadCmd::execute(const std::vector<std::string>& args)
{
	using namespace event;
	if (args.empty())
	{
		throw std::runtime_error("Command failed");
	}
	std::cout << consts::ui::FILE_LOADING_TEXT << '\n';
	try
	{
		master.updateSrcImg(args[0], 1);
	}
	catch (const std::exception&)
	{
		// add negative event to events
		master.getEvents().addEvent(GenericProgramEvent::openFail);
		return;
	}
	master.getHistory().resetHistory();
	master.getEvents().addEvent(GenericProgramEvent::openSuccess);
}

std::string LoadCmd::getDisplayName()
{
	return displayName;
}

std::string LoadCmd::getShortName()
{
	return shortName;
}
