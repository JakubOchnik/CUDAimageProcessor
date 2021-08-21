#include "UndoCmd.hpp"

void UndoCmd::execute(const std::string& args)
{
	master.getHistory().actionUndo();
}
