#include "ImgLoader.h"

bool ImgLoader::checkImgDims(int x, int y)
{
	int maxWidth, maxHeight;
	std::tie(maxWidth, maxHeight) = GpuInfo::getMaxDimensions();
	if (x > maxWidth || y > maxHeight) {
		return false;
	}
	return true;
}

Img ImgLoader::loadImg(const std::string& path, int type)
{
	cv::Mat img = cv::imread(path, type);
	if (!checkImgDims(img.size().width, img.size().height))
	{
		std::string msg = "Incorrect image dimensions: ";
		std::string dims = std::to_string(img.size().width) + "x" + std::to_string(img.size().height);
		msg += dims;
		throw std::exception(msg.c_str());
	}
	return Img(img, path);
}
Img ImgLoader::loadImg(const std::string& path)
{
	cv::Mat img = cv::imread(path, 0);

	if (img.data == nullptr)
	{
		std::string msg = "Could not load image from: " + path;
		throw std::exception(msg.c_str());
	}
	if (!checkImgDims(img.size().width, img.size().height))
	{
		std::string msg = "Incorrect image dimensions: ";
		std::string dims = std::to_string(img.size().width) + "x" + std::to_string(img.size().height);
		msg += dims;
		throw std::exception(msg.c_str());
	}
	return Img(img, path);
}