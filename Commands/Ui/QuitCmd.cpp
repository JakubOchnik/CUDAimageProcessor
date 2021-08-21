#include "QuitCmd.hpp"

void QuitCmd::execute(const std::string& args)
{
	master.exitApp();
}
