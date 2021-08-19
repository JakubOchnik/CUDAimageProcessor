#pragma once
#include "../BaseGenericCmd.hpp"
class ShowCmd : public BaseGenericCmd
{
	const std::string displayName = "ShowCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};