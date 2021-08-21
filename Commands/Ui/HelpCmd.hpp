#pragma once
#include "../BaseGenericCmd.hpp"
class HelpCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "HelpCommand";
	static inline const std::string shortName = "help";
	void execute(const std::string& args) override;
};