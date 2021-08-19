#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../ImgHandling/ImgLoader.h"
#include "../MainHandler/definitions.h"
#include "../Utilities/GPUcontrol.h"
#include "../Events/EventHistory.hpp"
#include "../Events/History.hpp"
#include "../UI/ui.h"

class MainHandler
{
	Img srcImg;
	Img dstImg;
	GPUcontroller GPUControl;
	EventHistory events;
	History history;

	bool quit = false;
	bool loaded = false;

public:
	MainHandler();

	Img* getSrcImg();
	Img& getDstImg();
	GPUcontroller* getGPUController();

	EventHistory& getEvents();
	History& getHistory();

	void updateDstImg(const Img& newImage);
	bool updateSrcImg(const std::string& newPath, int mode);
	void toggleLoaded();

	bool imgSave(const std::string& path);

	bool isQuit() const;
	bool isLoaded() const;
	void exitApp();
};
