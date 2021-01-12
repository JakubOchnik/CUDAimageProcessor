#include "mainHandler.h"

mainHandler::mainHandler():srcImg(Img()), dstImg(Img()) {
	
}
void mainHandler::actionHandler(enum action act) {

}
void mainHandler::actionRevert(int number) {

}
void mainHandler::actionUndo() {

}

Img* mainHandler::getSrcImg() {
	return &srcImg;
}
Img* mainHandler::getDstImg() {
	return &dstImg;
}

GPUcontroller* mainHandler::getGPUController() {
	return &GPUControl;
}

void mainHandler::updateDstImg(Img newImage) {
	dstImg = newImage;
}

bool mainHandler::updateSrcImg(std::string newPath, int mode) {
	Img newSrc = ImgLoader::loadImg(newPath, mode);
	if (newSrc.getImg()->empty()) {
		return false;
	}
	srcImg = newSrc;
	dstImg = srcImg;
	return true;
}

bool mainHandler::imgSave(std::string path) {
	if (dstImg.getStatus() && cv::imwrite(path, *dstImg.getImg())) {
		dstImg.setPath(path);
		return true;
	}
	return false;
}

std::vector<edit>* mainHandler::getHistory() {
	return &history;
}
