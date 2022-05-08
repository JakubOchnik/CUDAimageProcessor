#include <Utilities/GPUcontrol.hpp>

GPUcontroller::GPUcontroller()
{
	isMemAlloc = false;
	sizeUpdate = false;
	devImgPtr = nullptr;
	memSize = 0;
}

bool GPUcontroller::sizeUpdateStatus() const
{
	return sizeUpdate;
}

bool GPUcontroller::getGPUmemStatus() const
{
	return isMemAlloc;
}

bool GPUcontroller::GPUmalloc(Img* srcImg)
{
	if (isMemAlloc == true)
	{
		return false;
	}
	size_t dataSize = srcImg->getResolutionH() * srcImg->getResolutionW() * srcImg->getChannelNum() * sizeof(unsigned
		char);
	if (cudaMalloc((void**)&devImgPtr, dataSize) != cudaSuccess)
	{
		memSize = 0;
		devImgPtr = nullptr;
		return false;
	}
	// devImgPtr is allocated
	memSize = dataSize;
	cudaMemcpy(devImgPtr, srcImg->getImg()->data, dataSize, cudaMemcpyHostToDevice);
	isMemAlloc = true;
	sizeUpdate = false;
	return true;
}

void GPUcontroller::GPUfree()
{
	cudaFree(devImgPtr);
	isMemAlloc = false;
	sizeUpdate = false;
	devImgPtr = nullptr;
	memSize = 0;
}

bool GPUcontroller::updatePtr(Img* newImg)
{
	size_t newSize = newImg->getResolutionH() * newImg->getResolutionW() * newImg->getChannelNum() * sizeof(unsigned
		char);
	if (memSize != newSize)
	{
		GPUfree();
		if (!GPUmalloc(newImg))
		{
			return false;
		}
	}
	else
	{
		cudaMemcpy(devImgPtr, newImg->getImg()->data, newSize, cudaMemcpyHostToDevice);
	}
	return true;
}

unsigned char* GPUcontroller::getImgPtr()
{
	return devImgPtr;
}

GPUcontroller::~GPUcontroller()
{
	if (isMemAlloc)
	{
		printf("Freeing memory allocated on GPU (%d KB)...", memSize / 1024);
		// Sleep(1000); for debug
		GPUfree();
	}
}
