#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../ImgHandling/ImgLoader.h"
#include "../MainHandler/definitions.h"
#include "../Utilities/GPUcontrol.h"
#include "../Actions/ActionHandler.h"

#include <vector>

class MainHandler {
	Img srcImg;
	Img dstImg;
	std::vector<Edit> history;
	std::vector<Edit> redoHistory;
	GPUcontroller GPUControl;

public:
	MainHandler();
	void actionRedo();
	void actionUndo();

	Img* getSrcImg();
	Img* getDstImg();
	GPUcontroller* getGPUController();

	std::vector<Edit>* getHistory();
	void addToHistory(const std::string& value, Action type);

	void updateDstImg(const Img& newImage);
	bool updateSrcImg(const std::string& newPath, int mode);

	bool imgSave(const std::string& path);

};