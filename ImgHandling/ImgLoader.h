#pragma once
#include "ImgInfo.h"
#include "../Utilities/GPUinfo.h"

#include <opencv2/opencv.hpp>
#include <tuple>

class ImgLoader {
public:
	// checks if image dimensions are within the limit
	static bool checkImgDims(int x, int y);
	// multiple overloaded instances for better flexibility:
	static int loadImg(std::string path, int type, Img& src);
	static int loadImg(std::string path, Img& src);
	static Img loadImg(std::string path, int type);
	static Img loadImg(std::string path);
};