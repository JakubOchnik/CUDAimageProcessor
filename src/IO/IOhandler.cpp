#include <IO/IOhandler.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <ImgHandling/ImgLoader.hpp>
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include <string>

void IOHandler::saveImg(Img& img, const std::string& path)
{
	if (!img.getStatus())
	{
		std::string msg{"Image is not loaded"};
		throw std::runtime_error(msg.c_str());
	}

	if (!imwrite(path, img.getImg()))
	{
		std::string msg{"Could not save file at: " + path};
		throw std::runtime_error(msg.c_str());
	}
}

Img IOHandler::loadImg(const std::string& path, const int mode)
{
	Img newSrc;
	try
	{
		newSrc = ImgLoader::loadImg(path, mode);
	}
	catch (const std::runtime_error& ex)
	{
		throw;
	}
	return newSrc;
}
