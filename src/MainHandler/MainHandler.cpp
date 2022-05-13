#include <Consts/Errors.hpp>
#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <IO/IOhandler.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <ImgHandling/ImgLoader.hpp>
#include <MainHandler/MainHandler.hpp>
#include <UI/ui.hpp>
#include <Utilities/GPUcontrol.hpp>
#include <string>

MainHandler::MainHandler(bool gpu)
	: srcImg(Img()), dstImg(Img()), gpuEnabled(gpu)
{
}

Img& MainHandler::getSrcImg()
{
	return srcImg;
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
	// TODO: Use unified memory (huge performance improvement)
	if (gpuEnabled)
	{
		if (!GPUControl.getGPUmemStatus())
		{
			// mem is allocated, update ptr
			GPUControl.GPUmalloc(srcImg);
		}
		else
		{
			GPUControl.updatePtr(srcImg);
		}
	}
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
	dstImg.setPath(path);
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
