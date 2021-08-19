#pragma once
#include "../BaseGenericCmd.hpp"
class RedoCmd : public BaseGenericCmd
{
	const std::string displayName = "RedoCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};