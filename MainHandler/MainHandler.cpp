#include "MainHandler.h"

MainHandler::MainHandler() : srcImg(Img()), dstImg(Img())
{
}

Img* MainHandler::getSrcImg()
{
	return &srcImg;
}

Img& MainHandler::getDstImg()
{
	return dstImg;
}

GPUcontroller* MainHandler::getGPUController()
{
	return &GPUControl;
}

void MainHandler::updateDstImg(const Img& newImage)
{
	dstImg = newImage;
}

bool MainHandler::updateSrcImg(const std::string& newPath, int mode)
{
	Img newSrc = ImgLoader::loadImg(newPath, mode);
	if (newSrc.getImg()->empty())
	{
		return false;
	}
	srcImg = newSrc;
	dstImg = srcImg;

	return true;
}

bool MainHandler::imgSave(const std::string& path)
{
	if (dstImg.getStatus() && imwrite(path, *dstImg.getImg()))
	{
		dstImg.setPath(path);
		return true;
	}
	return false;
}

bool MainHandler::isQuit() const
{
	return quit;
}

void MainHandler::exitApp()
{
	quit = true;
}

bool MainHandler::isLoaded() const
{
	return loaded;
}

void MainHandler::toggleLoaded()
{
	loaded = !loaded;
}

EventHistory& MainHandler::getEvents()
{
	return events;
}

History& MainHandler::getHistory()
{
	return history;
}
