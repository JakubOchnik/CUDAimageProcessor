#include <Commands/GpuImg/InvertionCmd.hpp>

void InvertionCmd::execute(const std::vector<std::string>& args)
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

    executeInvertionKernel(dstImg, master.getGPUController());
}

std::string InvertionCmd::getDisplayName()
{
	return displayName;
}

std::string InvertionCmd::getShortName()
{
	return shortName;
}
