#include "ImgInfo.h"

Img::Img(cv::Mat img, std::string path): image(img) {
	this->path = path;
	resolutionH = img.size().height;
	resolutionW = img.size().width;
	colorChannels = img.channels();
	initiated = true;
}

Img::Img():initiated(false), image(cv::Mat()), colorChannels(0), resolutionH(0), resolutionW(0) {}

Img& Img::operator=(const Img& other) {
	this->colorChannels = other.colorChannels;
	this->initiated = other.initiated;
	this->resolutionH = other.resolutionH;
	this->resolutionW = other.resolutionW;
	this->path = other.path;
	this->image = other.image.clone();
	return *this;
}


std::string Img::getPath() const {
	return path;
}
unsigned int Img::getResolutionH() const {
	return resolutionH;
}
unsigned int Img::getResolutionW() const {
	return resolutionW;
}
unsigned int Img::getChannelNum() const {
	return colorChannels;
}
cv::Mat* Img::getImg() {
	return &image;
}

void Img::setPath(std::string newPath){
	path = newPath;
}
void Img::setResolutionH(int newResH) {
	resolutionH = newResH;
}
void Img::setResolutionW(int newResW) {
	resolutionW = newResW;
}
void Img::setChannelNum(int newBitDepth) {
	colorChannels = newBitDepth;
}
void Img::setImg(cv::Mat& newMat) {
	image = newMat;
}

void Img::updateAll(std::string newPath, cv::Mat& newMat) {
	setPath(newPath);
	setImg(newMat);
	setResolutionW(newMat.size().width);
	setResolutionH(newMat.size().height);
	setChannelNum(newMat.depth());
	initiated = true;
}
void Img::updateAll(cv::Mat& newMat) {
	setImg(newMat);
	setResolutionW(newMat.size().width);
	setResolutionH(newMat.size().height);
	setChannelNum(newMat.channels());
	initiated = true;
}

bool Img::getStatus() const {
	return initiated;
}