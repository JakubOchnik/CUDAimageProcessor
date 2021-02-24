#include "mainHandler.h"

mainHandler::mainHandler():srcImg(Img()), dstImg(Img()) {

}

bool mainHandler::actionRedo() {
	if (redoHistory.size()<1)
		return false;

	actionHandler::actionSelector(redoHistory.front().actionType, &dstImg, redoHistory.front().value, &GPUControl, true);
	actionHandler::updateGPUmem(&dstImg, &GPUControl, true);

	history.push_back(redoHistory.front());
	redoHistory.erase(redoHistory.begin());
	return true;
}
bool mainHandler::actionUndo() {
	Img newImg;
	newImg = srcImg;
	int i = 0;
	// perform all of the operations on source image besides from the latest one
	if (history.size() > 1)
	{
		for (auto a : history) {
			actionHandler::actionSelector(a.actionType, &newImg, a.value, &GPUControl,true);

			i++;
			if (i >= history.size() - 1) {
				break;
			}
		}
	}
	else if (history.size() == 0)
		return false;

	dstImg = newImg;

	actionHandler::updateGPUmem(&dstImg, &GPUControl, true);
	redoHistory.insert(redoHistory.begin(),history.back());
	// remove the lastest operation from the history
	history.pop_back();
	return true;
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
