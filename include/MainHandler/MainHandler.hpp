#pragma once
#include <ImgHandling/ImgInfo.hpp>
#include <ImgHandling/ImgLoader.hpp>
#include <Consts/Errors.hpp>
#include <Utilities/GPUcontrol.hpp>
#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <UI/ui.hpp>
#include <IO/IOhandler.hpp>
#include <Utilities/UnifiedPtr.hpp>

class MainHandler
{
	std::string sourcePath;
	Img dstImg;
	GPUcontroller GPUControl;
	EventHistory events;
	History history;

	bool quit{false};
	bool loaded{false};

public:
	MainHandler();

	Img& getDstImg();
	GPUcontroller* getGPUController();

	EventHistory& getEvents();
	History& getHistory();

	void updateDstImg(const Img& newImage);
	void updateDstImg(const std::string& newPath, int mode);
	void toggleLoaded();

	void imgSave(const std::string& path);

	std::string getSourceFilePath() const;

	bool isQuit() const;
	bool isLoaded() const;
	void exitApp();
};
