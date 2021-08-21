#pragma once
#include "../BaseGenericCmd.hpp"
#include "../../UI/UIdefinitions.h"
class LoadCmd : public BaseGenericCmd
{
	using BaseGenericCmd::BaseGenericCmd;
public:
	static inline const std::string displayName = "LoadCommand";
	static inline const std::string shortName = "load";
	void execute(const std::string& args);
};