#include "ShowCmd.hpp"

void ShowCmd::execute(MainHandler& master, const std::string& args)
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
