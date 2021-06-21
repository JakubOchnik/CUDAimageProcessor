#include "MainHandler.h"

MainHandler::MainHandler() :srcImg(Img()), dstImg(Img()) {

}

void MainHandler::actionRedo() {
	if (redoHistory.empty()) {
		throw Event::redoFail;
	}

	ActionHandler::actionSelector(redoHistory.front().actionType, &dstImg, redoHistory.front().value, &GPUControl, true);
	if (!ActionHandler::updateGPUmem(&dstImg, &GPUControl, true)) {
		throw Event::redoFail;
	}

	history.push_back(redoHistory.front());
	redoHistory.erase(redoHistory.begin());
}
void MainHandler::actionUndo() {
	Img newImg;
	newImg = srcImg;
	int i = 0;
	// perform all of the operations on source image besides from the latest one
	if (history.size() > 1)
	{
		for (auto a : history) {
			ActionHandler::actionSelector(a.actionType, &newImg, a.value, &GPUControl, true);

			i++;
			if (i >= history.size() - 1) {
				break;
			}
		}
	}
	else if (history.empty()) {
		throw Event::undoFail;
	}

	dstImg = newImg;

	if (!ActionHandler::updateGPUmem(&dstImg, &GPUControl, true)) {
		throw Event::GPUmallocFail;
	}
	redoHistory.insert(redoHistory.begin(), history.back());
	// remove the lastest operation from the history
	history.pop_back();
}

Img* MainHandler::getSrcImg() {
	return &srcImg;
}
Img* MainHandler::getDstImg() {
	return &dstImg;
}

GPUcontroller* MainHandler::getGPUController() {
	return &GPUControl;
}

void MainHandler::updateDstImg(Img newImage) {
	dstImg = newImage;
}

bool MainHandler::updateSrcImg(std::string newPath, int mode) {
	Img newSrc = ImgLoader::loadImg(newPath, mode);
	if (newSrc.getImg()->empty()) {
		return false;
	}
	srcImg = newSrc;
	dstImg = srcImg;

	return true;
}

bool MainHandler::imgSave(std::string path) {
	if (dstImg.getStatus() && cv::imwrite(path, *dstImg.getImg())) {
		dstImg.setPath(path);
		return true;
	}
	return false;
}

std::vector<Edit>* MainHandler::getHistory() {
	return &history;
}

void MainHandler::addToHistory(const std::string& value, Action type)
{
	std::vector<Edit>* ref = getHistory();
	ref->push_back(Edit{ value, type });
}
