#pragma once
#include "../BaseGenericCmd.hpp"
#include <iostream>
class HistoryCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "HistoryCommand";
	static inline const std::string shortName = "history";
	void execute(const std::string& args) override;
};