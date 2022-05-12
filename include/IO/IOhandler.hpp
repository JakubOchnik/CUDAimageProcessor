#pragma once

#include <ImgHandling/ImgLoader.hpp>
#include <string>

class IOHandler
{
public:
	static Img	loadImg(const std::string& path, int mode = 0);
	static void saveImg(Img& img, const std::string& path);
	// static void loadLUT(const std::string& path);
};