#pragma once
#include <opencv2/opencv.hpp>
#include "../ImgHandling/ImgInfo.h"
class IOHandler
{
	static cv::Mat loadImg(const std::string& path);
	static cv::Mat saveImg(Img img, const std::string& path);
public:

	//static void updateSrcImg(Img srcImg, Img dstImg, cv::);
};