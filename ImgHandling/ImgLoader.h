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
	static int loadImg(std::string path, int type, Img& dst);
	static int loadImg(std::string path, Img& dst);
	static Img loadImg(std::string path, int type);
	static Img loadImg(std::string path);
};
