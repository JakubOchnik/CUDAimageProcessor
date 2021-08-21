#pragma once
#include "../BaseGenericCmd.hpp"
class QuitCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "QuitCommand";
	static inline const std::string shortName = "quit";
	void execute(const std::string& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};