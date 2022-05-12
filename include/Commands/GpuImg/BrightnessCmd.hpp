#pragma once
#include <Commands/BaseEditCmd.hpp>

class BrightnessCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;

public:
	static inline const std::string displayName = "brightnessCommand";
	static inline const std::string shortName	= "brightness";

	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};