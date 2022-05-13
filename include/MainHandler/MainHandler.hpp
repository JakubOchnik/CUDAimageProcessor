#pragma once

#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <Utilities/GPUcontrol.hpp>
#include <memory>
#include <string>

class MainHandler
{
	Img							   srcImg;
	Img							   dstImg;
	std::shared_ptr<GPUcontroller> GPUControl;
	EventHistory				   events;
	History						   history;

	bool quit{false};
	bool loaded{false};
	bool gpuEnabled{false};

public:
	MainHandler(bool gpu);

	Img&						   getSrcImg();
	Img&						   getDstImg();
	std::shared_ptr<GPUcontroller> getGPUController();

	EventHistory& getEvents();
	History&	  getHistory();

	void updateDstImg(const Img& newImage);
	void updateSrcImg(const std::string& newPath, int mode);
	void toggleLoaded();

	void imgSave(const std::string& path);

	bool isQuit() const;
	bool isLoaded() const;
	void exitApp();
};
