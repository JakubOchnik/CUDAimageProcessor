#include "HistoryCmd.hpp"

void HistoryCmd::execute(const std::string& args)
{
	ui::printString(master.getHistory().getFormattedHistory());
	std::cout << "Press ENTER to return to main menu...";
	std::cin.get();
}
