#include "HelpCmd.hpp"

void HelpCmd::execute(const std::string& args)
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
