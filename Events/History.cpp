#include "History.hpp"

void History::actionRedo()
{
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
	/*
	Img newImg;
	newImg = srcImg;
	// perform all of the operations on source image besides from the latest one
	if (history.size() > 1)
	{
		int i{ 0 };
		for (const Edit& edit : history)
		{
			ActionHandler::actionSelector(edit.actionType, &newImg, edit.value, &GPUControl, true);

			i++;
			if (i >= history.size() - 1)
			{
				break;
			}
		}
	}
	else if (history.empty())
	{
		throw Event::undoFail;
	}

	dstImg = newImg;

	if (!ActionHandler::updateGPUmem(&dstImg, &GPUControl, true))
	{
		throw Event::GPUmallocFail;
	}
	redoHistory.insert(redoHistory.begin(), history.back());
	// remove the latest operation from the history
	history.pop_back();
	*/
}
std::vector<Edit>& History::getHistory()
{
	return history;
}

//TODO: Action type, change to sth else
void History::addToHistory(const std::string& value, Action type)
{
	history.push_back(Edit{ value, type });
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
	for (const auto& userAction : history)
	{
		std::string line = "[" + std::to_string(i);
		line += "] ";
		line += ACTION_TEXT_NAMES.at(userAction.actionType) + " ";
		line += " " + userAction.value;
		line += "\n";
		out += line;
		++i;
	}
	return out;
}