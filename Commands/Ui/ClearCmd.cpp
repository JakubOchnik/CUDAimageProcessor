#include "ClearCmd.hpp"

void ClearCmd::execute(MainHandler& master, const std::string& args)
{
	master.getEvents().clearEvents();
}
