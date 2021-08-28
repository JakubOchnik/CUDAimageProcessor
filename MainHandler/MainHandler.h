#pragma once
#include "../ImgHandling/ImgInfo.h"
#include "../ImgHandling/ImgLoader.h"
#include "Errors.hpp"
#include "../Utilities/GPUcontrol.h"
#include "../Events/EventHistory.hpp"
#include "../Events/History.hpp"
#include "../UI/ui.h"
#include "../IO/IOhandler.hpp"

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

	Img& getSrcImg();
	Img& getDstImg();
	GPUcontroller* getGPUController();

	EventHistory& getEvents();
	History& getHistory();

	void updateDstImg(const Img& newImage);
	void updateSrcImg(const std::string& newPath, int mode);
	void toggleLoaded();

	void imgSave(const std::string& path);

	bool isQuit() const;
	bool isLoaded() const;
	void exitApp();
};
