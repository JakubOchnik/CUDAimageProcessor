#include "ImgLoader.h"

bool ImgLoader::checkImgDims(int x, int y) {
	int maxWidth, maxHeight;
	std::tie(maxWidth, maxHeight) = GpuInfo::getMaxDimensions();
	if (x > maxWidth || y > maxHeight) {
		return false;
	}
	return true;
}

int ImgLoader::loadImg(std::string path, int type, Img& dst) {
	cv::Mat img = cv::imread(path, type);
	if (!checkImgDims(img.size().width, img.size().height))
		return -1;
	dst.updateAll(path, img);
	return 0;
}
int ImgLoader::loadImg(std::string path, Img& dst) {
	cv::Mat img = cv::imread(path, 0);
	if (!checkImgDims(img.size().width, img.size().height))
		return -1;
	dst.updateAll(path, img);
	return 0;
}
Img ImgLoader::loadImg(std::string path, int type) {
	cv::Mat img = cv::imread(path, type);
	if (!checkImgDims(img.size().width, img.size().height))
		return Img();
	return Img(img, path);
}
Img ImgLoader::loadImg(std::string path) {
	cv::Mat img = cv::imread(path, 0);
	if (!checkImgDims(img.size().width, img.size().height))
		return Img();
	return Img(img, path);
}