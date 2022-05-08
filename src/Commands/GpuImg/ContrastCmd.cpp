#include <Commands/GpuImg/ContrastCmd.hpp>

void ContrastCmd::execute(const std::vector<std::string>& args)
{
    if (!master.isLoaded())
    {
        throw Error::NotLoadedFail();
    }
    if (args.size() != 1)
	{
		throw Error::ParamFail();
	}
    std::vector<int> parsedArgs{TextUtils::tokensToNumbers(args)};
    const int contrast{parsedArgs[0]};
    if (contrast < -255 || contrast > 255)
    {
        throw Error::ParamFail();
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
