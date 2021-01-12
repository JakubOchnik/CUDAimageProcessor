#pragma once
#include <opencv2/opencv.hpp>
#include "ImgInfo.h"

class ImgLoader {
public:
	static void loadImg(std::string path, int type, Img& src);
	static void loadImg(std::string path, Img& src);
	static Img loadImg(std::string path, int type);
	static Img loadImg(std::string path);
};