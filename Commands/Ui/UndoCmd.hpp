#pragma once
#include "../BaseGenericCmd.hpp"
class UndoCmd : public BaseGenericCmd
{
	const std::string displayName = "UndoCommand";
public:
	void execute(MainHandler& master, const std::string& args) override;
};