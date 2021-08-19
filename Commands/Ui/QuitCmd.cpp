#include "QuitCmd.hpp"

void QuitCmd::execute(MainHandler& master, const std::string& args)
{
	master.exitApp();
}
