#pragma once
#include "../BaseGenericCmd.hpp"
class SaveCmd : public BaseGenericCmd
{
	const std::string displayName = "QuitCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};