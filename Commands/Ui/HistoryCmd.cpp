#include "HistoryCmd.hpp"

void HistoryCmd::execute(MainHandler& master, const std::string& args)
{
	ui::printString(master.getHistory().getFormattedHistory());
}
