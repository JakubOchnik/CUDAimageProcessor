#pragma once
#include "ImgInfo.h"
#include "../Utilities/GpuInfo.h"

#include <opencv2/opencv.hpp>
#include <tuple>

class ImgLoader
{
public:
	// checks if image dimensions are within the limit
	static bool checkImgDims(int x, int y);
	// multiple overloaded instances for better flexibility:
	static Img loadImg(const std::string& path, int type);
	static Img loadImg(const std::string& path);
};
