#include "RedoCmd.hpp"

void RedoCmd::execute(const std::vector<std::string>& args)
{
	master.getHistory().actionRedo();
}

std::string RedoCmd::getDisplayName()
{
	return displayName;
}

std::string RedoCmd::getShortName()
{
	return shortName;
}
