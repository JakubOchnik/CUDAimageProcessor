#include "LoadCmd.hpp"

void LoadCmd::execute(const std::string& args)
{
	/*
	if (args.length() < 2)
	{
		throw Event::commandFail;
	}
	std::cout << FILE_LOADING_TEXT << '\n';
	// TODO: proper error handling
	if (master.updateSrcImg(args, 1))
	{
		//todo
		//eventQueue.push_back(Event::openSuccess);
		master.resetHistory();
		master.toggleLoaded();
		return;
	}
	*/
	throw Event::openFail;
}
