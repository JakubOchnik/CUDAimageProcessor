#pragma once
#include <Commands/BaseGenericCmd.hpp>

class ClearCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "ClearCommand";
	static inline const std::string shortName	= "clear";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};