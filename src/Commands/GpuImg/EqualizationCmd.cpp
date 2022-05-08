#include <Commands/GpuImg/EqualizationCmd.hpp>

void EqualizationCmd::execute(const std::vector<std::string>& args)
{
	if (!master.isLoaded())
	{
		throw Error::NotLoadedFail();
	}
	if (!args.empty())
	{
		throw Error::ParamFail();
	}

	Img& dstImg{master.getDstImg()};

	executeEqualizationKernel(dstImg, master.getGPUController());
}

std::string EqualizationCmd::getDisplayName()
{
	return displayName;
}

std::string EqualizationCmd::getShortName()
{
	return shortName;
}
