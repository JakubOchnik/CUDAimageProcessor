#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../ImgHandling/ImgLoader.h"
#include "../MainHandler/definitions.h"
#include "../Utilities/GPUcontrol.h"
#include "../Actions/actionHandler.h"
#include <vector>
class mainHandler {
private:
	Img srcImg;
	Img dstImg;
	std::vector<edit> history;
	std::vector<edit> redoHistory;
	GPUcontroller GPUControl;

public:
	mainHandler();
	bool actionRedo();
	bool actionUndo();

	Img* getSrcImg();
	Img* getDstImg();
	GPUcontroller* getGPUController();

	std::vector<edit>* getHistory();

	void updateDstImg(Img newImage);
	bool updateSrcImg(std::string newPath, int mode);

	bool imgSave(std::string path);

};