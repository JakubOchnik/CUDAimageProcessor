#pragma once
#include <Commands/BaseGenericCmd.hpp>
#include <Events/History.hpp>

class RedoCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "RedoCommand";
	static inline const std::string shortName = "redo";
	void execute(const std::vector<std::string>& args) override;

	std::string getShortName() override;
	std::string getDisplayName() override;
};