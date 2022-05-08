#pragma once
#include <Commands/BaseGenericCmd.hpp>
#include <Events/History.hpp>
#include <MainHandler/MainHandler.hpp>
#include <UI/UIdefinitions.hpp>

class LoadCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;

public:
	static inline const std::string displayName = "LoadCommand";
	static inline const std::string shortName	= "load";
	void execute(const std::vector<std::string>& args);

	std::string getShortName() override;
	std::string getDisplayName() override;
};