#pragma once
#include <Commands/BaseGenericCmd.hpp>

class SaveCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "QuitCommand";
	static inline const std::string shortName	= "save";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};