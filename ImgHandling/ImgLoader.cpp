#include "ImgLoader.h"

void ImgLoader::loadImg(std::string path, int type, Img& dst) {
	cv::Mat img = cv::imread(path, type);
	dst.updateAll(path, img);
}
void ImgLoader::loadImg(std::string path, Img& dst) {
	cv::Mat img = cv::imread(path, 0);
	dst.updateAll(path, img);
}
Img ImgLoader::loadImg(std::string path, int type) {
	cv::Mat img = cv::imread(path, type);
	return Img(img, path);
}
Img loadImg(std::string path) {
	cv::Mat img = cv::imread(path, 0);
	return Img(img, path);
}