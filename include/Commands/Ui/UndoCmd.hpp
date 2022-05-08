#pragma once
#include <Commands/BaseGenericCmd.hpp>
#include <Events/History.hpp>

class UndoCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "UndoCommand";
	static inline const std::string shortName	= "undo";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};