#pragma once
#include <MainHandler/definitions.hpp>
#include <UI/UIdefinitions.hpp>
#include <iostream>
#include <memory>
#include <vector>

struct Edit
{
	std::string				 shortName;
	std::string				 longerName;
	std::vector<std::string> args;
};

class History
{

	std::vector<Edit> history;
	std::vector<Edit> redoHistory;

	static std::string tokensToLine(const std::vector<std::string>& tokens);

public:
	void actionRedo();
	void actionUndo();
	void addToHistory(std::string			   snm,
					  std::string			   lnm,
					  std::vector<std::string> args);
	void resetHistory();

	[[nodiscard]] const std::vector<Edit>& getHistory() const;
	[[nodiscard]] const std::vector<Edit>& getRedoHistory() const;

	[[nodiscard]] size_t	  size() const;
	[[nodiscard]] size_t	  sizeRd() const;
	[[nodiscard]] std::string getFormattedHistory() const;
};
