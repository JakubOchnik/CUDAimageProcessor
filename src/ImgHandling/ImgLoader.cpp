#include <Consts/Errors.hpp>
#include <ImgHandling/ImgLoader.hpp>
#include <Utilities/GPUinfo.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <tuple>

bool ImgLoader::checkImgDims(int x, int y)
{
	int maxWidth, maxHeight;
	std::tie(maxWidth, maxHeight) = GpuInfo::getMaxDimensions();
	return !(x > maxWidth || y > maxHeight);
}

Img ImgLoader::loadImg(const std::string& path, int type)
{
	cv::Mat img{cv::imread(path, type)};
	if (!img.data)
	{
		throw std::runtime_error("Incorrect path");
	}
	if (!checkImgDims(img.size().width, img.size().height))
	{
		std::string msg{"Incorrect image dimensions: "};
		std::string dims{std::to_string(img.size().width) + "x"
						 + std::to_string(img.size().height)};
		msg += dims;
		throw std::runtime_error(msg.c_str());
	}
	return Img(img, path);
}
Img ImgLoader::loadImg(const std::string& path)
{
	cv::Mat img{cv::imread(path, 0)};

	if (!img.data)
	{
		std::string msg{"Could not load image from: " + path};
		throw std::runtime_error(msg.c_str());
	}
	if (!checkImgDims(img.size().width, img.size().height))
	{
		std::string msg{"Incorrect image dimensions: "};
		std::string dims{std::to_string(img.size().width) + "x"
						 + std::to_string(img.size().height)};
		msg += dims;
		throw std::runtime_error(msg.c_str());
	}
	return Img(img, path);
}