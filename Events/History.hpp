#pragma once
#include "../MainHandler/definitions.h"
#include "../UI/UIdefinitions.h"
#include <vector>
#include <iostream>
class History
{
	std::vector<Edit> history;
	std::vector<Edit> redoHistory;
public:
	void actionRedo();
	void actionUndo();
	std::vector<Edit>& getHistory();
	//TODO: Action type, change to sth else
	void addToHistory(const std::string& value, Action type);
	void resetHistory();
	std::string getFormattedHistory() const;
};
