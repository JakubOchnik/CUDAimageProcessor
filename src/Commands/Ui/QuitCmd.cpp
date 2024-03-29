#include <Commands/Ui/QuitCmd.hpp>

void QuitCmd::execute(const std::vector<std::string>& args)
{
	master.exitApp();
}

std::string QuitCmd::getDisplayName()
{
	return displayName;
}

std::string QuitCmd::getShortName()
{
	return shortName;
}
