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
		throw event::error::NotLoadedFail();
	}

	if (args.size() != 2)
	{
		throw event::error::ParamFail();
	}

	std::vector<int> parsedArgs{TextUtils::tokensToNumbers(args)};

	const int w{parsedArgs[0]}, h{parsedArgs[1]};
	if (w < 0 || h < 0)
	{
		throw event::error::ParamFail();
	}

	// Execute the resize action
	resizeAction(cv::Size(w, h));
}

void ResizeCmd::resizeAction(const cv::Size& size)
{
	Img& dstImg{master.getDstImg()};

	cv::Mat newImg(dstImg.getImg());

	cv::resize(dstImg.getImg(), newImg, size);
	dstImg.updateAll(newImg);
}
