#include "ClearCmd.hpp"

void ClearCmd::execute(const std::string& args)
{

	master.getEvents().clearEvents();
}
