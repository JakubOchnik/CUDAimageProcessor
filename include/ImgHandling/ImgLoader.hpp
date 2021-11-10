#pragma once
#include <ImgHandling/ImgInfo.hpp>
#include <Utilities/GPUinfo.hpp>
#include <Consts/Errors.hpp>

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
