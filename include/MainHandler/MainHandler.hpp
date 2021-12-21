#pragma once
#include <ImgHandling/ImgInfo.hpp>
#include <ImgHandling/ImgLoader.hpp>
#include <Consts/Errors.hpp>
#include <Utilities/GPUcontrol.hpp>
#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <UI/ui.hpp>
#include <IO/IOhandler.hpp>

class MainHandler
{
	Img srcImg;
	Img dstImg;
	GPUcontroller GPUControl;
	EventHistory events;
	History history;

	bool quit{false};
	bool loaded{false};
	bool gpuEnabled{false};

public:
	MainHandler(bool gpu);

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