#pragma once
#include "../BaseGenericCmd.hpp"
class RedoCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "RedoCommand";
	static inline const std::string shortName = "redo";
	void execute(const std::string& args) override;
};