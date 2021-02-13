#include "ImgLoader.h"

bool checkImgDims(int x, int y) {
	int maxWidth, maxHeight;
	tie(maxWidth, maxHeight) = GPUinfo::getMaxDimensions();
	if (x > maxWidth || y > maxHeight) {
		return 0;
	}
	return 1;
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
Img loadImg(std::string path) {
	cv::Mat img = cv::imread(path, 0);
	if (!checkImgDims(img.size().width, img.size().height))
		return Img();
	return Img(img, path);
}