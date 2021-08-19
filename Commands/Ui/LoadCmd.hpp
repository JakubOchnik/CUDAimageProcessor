#pragma once
#include "../BaseGenericCmd.hpp"
#include "../../UI/UIdefinitions.h"
class LoadCmd : public BaseGenericCmd
{
	const std::string displayName = "LoadCommand";
public:
	void execute(MainHandler& master, const std::string& args);
};