#pragma once
#include <Commands/BaseEditCmd.hpp>

class EqualizationCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;

public:
	static inline const std::string displayName = "equalizationCommand";
	static inline const std::string shortName	= "equalize";

	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};
