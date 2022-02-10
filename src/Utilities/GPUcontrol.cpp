#include <Utilities/GPUcontrol.hpp>
#include <windows.h>

GPUcontroller::GPUcontroller()
{
	sizeUpdate = false;
}

bool GPUcontroller::sizeUpdateStatus() const
{
	return sizeUpdate;
}

bool GPUcontroller::getGPUmemStatus() const
{
	return data.isAlloc();
}

UnifiedPtr &GPUcontroller::createGpuPointer(unsigned char *inputData, size_t dataSize)
{
	data = std::move(UnifiedPtr(inputData, dataSize));
	return data;
}

bool GPUcontroller::updatePtr(Img *newImg)
{
	size_t newSize = newImg->getResolutionH() * newImg->getResolutionW() * newImg->getChannelNum() * sizeof(unsigned char);
	if (data.size() != newSize)
	{
		try
		{
			data = std::move(UnifiedPtr(newImg->getImg()->data, newSize));
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
	}
	else
	{
		std::memcpy(data.getPtr(), newImg->getImg()->data, newSize);
	}
	return true;
}

UnifiedPtr &GPUcontroller::getImgPtr()
{
	return data;
}

GPUcontroller::~GPUcontroller()
{
	if (data.isAlloc())
	{
		printf("Freeing memory allocated on GPU (%zd KB)...", data.size() / 1024);
		// Sleep(1000); for debug
	}
}
