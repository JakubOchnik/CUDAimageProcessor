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

void MainHandler::updateSrcImg(const std::string& newPath, int mode)
{
	try
	{
		srcImg = IOHandler::loadImg(newPath, 1);
	}
	catch (const std::exception& ex)
	{
		throw;
	}
	dstImg = srcImg;
	loaded = true;
}

void MainHandler::imgSave(const std::string& path)
{
	try
	{
		IOHandler::saveImg(dstImg, path);
	}
	catch (const std::exception& ex)
	{
		throw;
	}
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
