#include <Commands/Ui/HelpCmd.hpp>

void HelpCmd::execute(const std::vector<std::string>& args)
{
	ui::helpScreen();
}

std::string HelpCmd::getDisplayName()
{
	return displayName;
}

std::string HelpCmd::getShortName()
{
	return shortName;
}
