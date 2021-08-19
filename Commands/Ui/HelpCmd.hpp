#pragma once
#include "../BaseGenericCmd.hpp"
class ClearCmd : public BaseGenericCmd
{
	const std::string displayName = "ClearCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};