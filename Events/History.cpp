#include "History.hpp"


void History::actionRedo()
{
	history.push_back(redoHistory.front());
	redoHistory.erase(redoHistory.begin());
	/*
	if (redoHistory.empty())
	{
		throw Event::redoFail;
	}
	//TODO:Perform all the previous actions
	//ActionHandler::actionSelector(redoHistory.front().actionType, &dstImg, redoHistory.front().value, &GPUControl,
		//true);
	//if (!ActionHandler::updateGPUmem(&dstImg, &GPUControl, true))
	//{
	//	throw Event::redoFail;
	//}

	history.push_back(redoHistory.front());
	redoHistory.erase(redoHistory.begin());
	*/
}
void History::actionUndo()
{
	redoHistory.insert(redoHistory.begin(), history.back());
	// remove the latest operation from the history
	history.pop_back();
}

void History::addToHistory(const std::string snm, const std::string lnm, const std::vector<std::string> args)
{
	history.emplace_back(Edit{ snm, lnm, args });
}

void History::resetHistory()
{
	history.clear();
}

std::string History::getFormattedHistory() const
{
	std::string out = "-- EDIT HISTORY -- \n";
	if (history.empty())
	{
		out += "History is empty. \n";
	}

	int i = 1;
	for (const auto& [snm, lnm, args] : history)
	{
		const std::string line = "[" + std::to_string(i) + "] " + lnm + " " + tokensToLine(args) + "\n";
		out += line;
		++i;
	}
	return out;
}

std::string History::tokensToLine(const std::vector<std::string>& tokens)
{
	std::string line;
	for (const auto& token : tokens)
	{
		line += (token + " ");
	}
	return line;
}

size_t History::size() const
{
	return history.size();
}

size_t History::sizeRd() const
{
	return redoHistory.size();
}

const std::vector<Edit>& History::getHistory() const
{
	return history;
}
const std::vector<Edit>& History::getRedoHistory() const
{
	return redoHistory;
}
