#pragma once
#include <Commands/BaseEditCmd.hpp>

class InvertionCmd : public BaseEditCmd
{
	using BaseEditCmd::BaseEditCmd;

public:
	static inline const std::string displayName = "invertionCommand";
	static inline const std::string shortName	= "invert";

	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};
