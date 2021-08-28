#pragma once
#include "../MainHandler/definitions.h"
#include "../UI/UIdefinitions.h"
#include <memory>
#include <vector>
#include <iostream>
class History
{
	struct Edit
	{
		const std::string shortName;
		const std::string longerName;
		const std::vector<std::string> args;
	};

	std::vector<Edit> history;
	std::vector<Edit> redoHistory;

	static std::string tokensToLine(const std::vector<std::string>& tokens);

public:
	void actionRedo();
	void actionUndo();
	void addToHistory(std::string snm, std::string lnm, std::vector<std::string> args);
	void resetHistory();
	[[nodiscard]] std::string getFormattedHistory() const;
};
