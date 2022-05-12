#include <Commands/GpuImg/ContrastCmd.hpp>
#include <Commands/GpuImg/Kernels/ContrastKernel.cuh>

void ContrastCmd::execute(const std::vector<std::string>& args)
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
	const int		 contrast{parsedArgs[0]};
	if (contrast < -255 || contrast > 255)
	{
		throw event::error::ParamFail();
	}
	Img& dstImg{master.getDstImg()};
	executeContrastKernel(dstImg, contrast, master.getGPUController());
}

std::string ContrastCmd::getDisplayName()
{
	return displayName;
}

std::string ContrastCmd::getShortName()
{
	return shortName;
}
