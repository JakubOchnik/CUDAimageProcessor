#include "RedoCmd.hpp"

void RedoCmd::execute(const std::string& args)
{
	master.getHistory().actionRedo();
}
