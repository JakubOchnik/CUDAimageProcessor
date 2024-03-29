#include <Commands/GpuImg/BrightnessCmd.hpp>
#include <Commands/GpuImg/Kernels/BrightnessKernel.cuh>

void BrightnessCmd::execute(const std::vector<std::string>& args)
{
	if (!master.isLoaded())
	{
		throw event::error::NotLoadedFail();
	}
	if (args.size() != 1)
	{
		throw event::error::ParamFail();
	}

	std::vector<int> parsedArgs{TextUtils::tokensToNumbers(args)};

	const int shift{parsedArgs[0]};
	Img&	  dstImg{master.getDstImg()};

	executeBrightnessKernel(dstImg, shift, master.getGPUController());
}

std::string BrightnessCmd::getDisplayName()
{
	return displayName;
}

std::string BrightnessCmd::getShortName()
{
	return shortName;
}
