#pragma once
#include <Commands/BaseGenericCmd.hpp>

class ShowCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "ShowCommand";
	static inline const std::string shortName	= "show";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};