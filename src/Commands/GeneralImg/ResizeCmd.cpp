#include <Commands/GeneralImg/ResizeCmd.hpp>

std::string ResizeCmd::getDisplayName()
{
	return displayName;
}

std::string ResizeCmd::getShortName()
{
	return shortName;
}

void ResizeCmd::execute(const std::vector<std::string>& args)
{
	if (!master.isLoaded())
	{
		throw Error::NotLoadedFail();
	}

	if (args.size() != 2)
	{
		throw Error::ParamFail();
	}

	std::vector<int> parsedArgs{TextUtils::tokensToNumbers(args)};

	const int w{ parsedArgs[0] }, h{ parsedArgs[1] };
	if (w < 0 || h < 0)
	{
		throw Error::ParamFail();
	}

	// Execute the resize action
	resizeAction(cv::Size(w,h));

}

void ResizeCmd::resizeAction(cv::Size& size)
{
	Img& dstImg{master.getDstImg()};

	cv::Mat newImg(*dstImg.getImg());

	cv::resize(*dstImg.getImg(), newImg, size);
	dstImg.updateAll(newImg);
}
