#include <Commands/GeneralImg/CropCmd.hpp>

void CropCmd::execute(const std::vector<std::string>& args)
{
	if (!master.isLoaded())
	{
		throw Error::NotLoadedFail();
	}
	if (args.size() != 4)
	{
		throw Error::ParamFail();
	}

	std::vector<int> parsedArgs{TextUtils::tokensToNumbers(args)};

	const int x{parsedArgs[0]}, y{parsedArgs[1]}, w{parsedArgs[2]},
		h{parsedArgs[3]};
	if (x < 0 || y < 0 || w <= 0 || h <= 0)
	{
		throw Error::ParamFail();
	}

	Img& dstImg{master.getDstImg()};

	if (x + w > dstImg.getResolutionW() || y + h > dstImg.getResolutionH())
	{
		throw Error::ParamFail();
	}
	// calculate the crop area
	cv::Rect area(x, y, w, h);

	// execute the action
	cropAction(area);
}

void CropCmd::cropAction(cv::Rect& area)
{
	Img&	dstImg{master.getDstImg()};
	cv::Mat newImg(*dstImg.getImg());
	newImg = newImg(area);
	dstImg.updateAll(newImg);
}

std::string CropCmd::getDisplayName()
{
	return displayName;
}

std::string CropCmd::getShortName()
{
	return shortName;
}
