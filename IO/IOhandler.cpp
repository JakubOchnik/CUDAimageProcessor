#include "IOhandler.hpp"

void IOHandler::saveImg(Img& img, const std::string& path)
{
	if (!img.getStatus())
	{
		std::string msg = "Image is not loaded";
		throw std::exception(msg.c_str());
	}

	if (!imwrite(path, *img.getImg()))
	{
		std::string msg = "Could not save file at: " + path;
		throw std::exception(msg.c_str());
	}
}

Img IOHandler::loadImg(const std::string& path, const int mode)
{
	Img newSrc;
	try
	{
		newSrc = ImgLoader::loadImg(path, mode);
	}
	catch (const std::exception& ex)
	{
		throw;
	}
	return newSrc;
}