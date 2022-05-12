#include <Commands/Ui/HistoryCmd.hpp>
#include <UI/ui.hpp>

void HistoryCmd::execute(const std::vector<std::string>& args)
{
	ui::printString(master.getHistory().getFormattedHistory());
	std::cout << "Press ENTER to return to main menu...";
	std::cin.get();
}

std::string HistoryCmd::getDisplayName()
{
	return displayName;
}

std::string HistoryCmd::getShortName()
{
	return shortName;
}
