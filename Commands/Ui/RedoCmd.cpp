#include "RedoCmd.hpp"

void RedoCmd::execute(MainHandler& master, const std::string& args)
{
	master.getHistory().actionRedo();
}
