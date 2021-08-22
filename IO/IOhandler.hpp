#pragma once
#include <opencv2/opencv.hpp>
#include <stdexcept>
#include "../ImgHandling/ImgInfo.h"
#include "../ImgHandling/ImgLoader.h"
class IOHandler
{
public:
	static Img loadImg(const std::string& path, int mode = 0);
	static void saveImg(Img& img, const std::string& path);
	// static void loadLUT(const std::string& path);
};