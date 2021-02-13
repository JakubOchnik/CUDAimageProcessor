#pragma once
#include <opencv2/opencv.hpp>
#include "ImgInfo.h"
#include "../Utilities/GPUinfo.h"
#include <tuple>

class ImgLoader {
public:
	static bool checkImgDims(int x, int y);
	static int loadImg(std::string path, int type, Img& src);
	static int loadImg(std::string path, Img& src);
	static Img loadImg(std::string path, int type);
	static Img loadImg(std::string path);
};