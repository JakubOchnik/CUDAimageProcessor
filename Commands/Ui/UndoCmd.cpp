#include "UndoCmd.hpp"

void UndoCmd::execute(MainHandler& master, const std::string& args)
{
	master.getHistory().actionUndo();
}
