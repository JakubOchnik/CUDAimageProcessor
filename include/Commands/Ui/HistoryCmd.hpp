#pragma once
#include <iostream>
#include <Commands/BaseGenericCmd.hpp>

class HistoryCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "HistoryCommand";
	static inline const std::string shortName = "history";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};