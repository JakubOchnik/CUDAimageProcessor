#pragma once
#include <ImgHandling/ImgInfo.hpp>
#include <string>

class ImgLoader
{
public:
	// checks if image dimensions are within the limit
	static bool checkImgDims(int x, int y);
	// multiple overloaded instances for better flexibility:
	static Img loadImg(const std::string& path, int type);
	static Img loadImg(const std::string& path);
};
