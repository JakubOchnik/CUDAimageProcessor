#pragma once
#include "../BaseGenericCmd.hpp"
class HistoryCmd : public BaseGenericCmd
{
	const std::string displayName = "HistoryCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};