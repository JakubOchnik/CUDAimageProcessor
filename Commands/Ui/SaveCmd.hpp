#pragma once
#include "../BaseGenericCmd.hpp"
class SaveCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "QuitCommand";
	static inline const std::string shortName = "save";
	void execute(const std::string& args) override;
};