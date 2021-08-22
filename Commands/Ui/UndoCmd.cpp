#include "UndoCmd.hpp"

void UndoCmd::execute(const std::vector<std::string>& args)
{
	master.getHistory().actionUndo();
}

std::string UndoCmd::getDisplayName()
{
	return displayName;
}

std::string UndoCmd::getShortName()
{
	return shortName;
}
