#include <Commands/Ui/ClearCmd.hpp>

void ClearCmd::execute(const std::vector<std::string>& args)
{

	master.getEvents().clearEvents();
}

std::string ClearCmd::getDisplayName()
{
	return displayName;
}

std::string ClearCmd::getShortName()
{
	return shortName;
}
