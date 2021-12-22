#include <MainHandler/MainHandler.hpp>


MainHandler::MainHandler(bool gpu) : dstImg(Img()), gpuEnabled(gpu)
{
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

void MainHandler::updateDstImg(const std::string& newPath, int mode)
{
	sourcePath = newPath;
	try
	{
		dstImg = IOHandler::loadImg(newPath, 1);
	}
	catch (const std::exception& ex)
	{
		throw;
	}
	loaded = true;
	// TODO: Use unified memory (huge performance improvement)
	if(gpuEnabled)
	{
		if(!GPUControl.getGPUmemStatus())
		{
			// mem is allocated, update ptr
			GPUControl.GPUmalloc(&dstImg);
		}
		else
		{
			GPUControl.updatePtr(&dstImg);
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

std::string MainHandler::getSourceFilePath() const
{
	return sourcePath;
}
