#pragma once
#include <Commands/BaseGenericCmd.hpp>

class HelpCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "HelpCommand";
	static inline const std::string shortName	= "help";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};