#include "mainHandler.h"

mainHandler::mainHandler():srcImg(Img()), dstImg(Img()) {
	
}

void mainHandler::actionRevert(int number) {

}
void mainHandler::actionUndo() {
	Img newImg;
	newImg = srcImg;
	cv::imshow("pre newImg", *newImg.getImg());
	cv::imshow("pre srcImg", *srcImg.getImg());
	cv::imshow("pre dstImg", *dstImg.getImg());
	//newImg.setImg(srcImg.getImg()->clone());
	// perform all the previous operations on source image besides from the most recent one
	/*
	crop,
	brightness,
	contrast,
	histogram,
	equalization,
	invertion,
	resize
	*/
	int i = 0;
	if (history.size() > 1)
	{
		for (auto a : history) {
			actionHandler::actionSelector(a.actionType, &newImg, a.value, &GPUControl,true);
			/*switch (a.actionType) {
			case crop:
				break;
			case brightness:
				actionHandler::actionSelector(brightness, &newImg, a.value, &GPUControl);
				break;
			case contrast:
				actionHandler::actionSelector(contrast, &newImg, a.value, &GPUControl);
				break;
			case histogram:
				break;
			case equalization:
				break;
			case invertion:
				break;
			case resize:
				break;
			default:
				break;
			}*/
			i++;
			if (i >= history.size() - 1) {
				break;
			}
		}
	}
	cv::imshow("1 newImg", *newImg.getImg());
	cv::imshow("1 srcImg", *srcImg.getImg());
	cv::imshow("1 dstImg", *dstImg.getImg());
	dstImg = newImg;
	cv::imshow("2 newImg", *newImg.getImg());
	cv::imshow("2 srcImg", *srcImg.getImg());
	cv::imshow("2 dstImg", *dstImg.getImg());
	cv::waitKey(0);
	cv::destroyAllWindows();
	actionHandler::updateGPUmem(&dstImg, &GPUControl, true);
	// history
	history.pop_back();
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
	//dstImg.setImg(srcImg.getImg()->clone());
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
