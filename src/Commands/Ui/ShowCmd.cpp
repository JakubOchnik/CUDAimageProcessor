#include <Commands/Ui/ShowCmd.hpp>

void ShowCmd::execute(const std::vector<std::string>& args)
{
	if (args.empty())
	{
		ui::showPreview(master.getDstImg());
	}
	else
	{
		using namespace boost;
		try
		{
			const int scale{lexical_cast<int>(args[0])};
			ui::showPreview(master.getDstImg(), scale);
		}
		catch (bad_lexical_cast&)
		{
			throw event::error::ParamFail();
		}
	}
}

std::string ShowCmd::getDisplayName()
{
	return displayName;
}

std::string ShowCmd::getShortName()
{
	return shortName;
}
