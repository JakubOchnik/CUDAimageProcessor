#include "ShowCmd.hpp"

void ShowCmd::execute(const std::string& args)
{
	int scale = 0;
	if (args.find(' ') != std::string::npos)
	{
		auto value = args.substr(args.find(' '));
		value.erase(0, 1);
		scale = stoi(value);
	}
	ui::showPreview(master.getDstImg(), scale);
}

std::string ShowCmd::getDisplayName()
{
	return displayName;
}

std::string ShowCmd::getShortName()
{
	return shortName;
}
