#pragma once

#include <ImgHandling/ImgInfo.hpp>

class GPUcontroller
{
private:
	bool		   isMemAlloc;
	bool		   sizeUpdate;
	unsigned char* devImgPtr;
	unsigned int   memSize;

public:
	GPUcontroller();

	unsigned char* getImgPtr() const;
	bool		   getGPUmemStatus() const;
	bool		   sizeUpdateStatus() const;

	bool updatePtr(const Img& newImg);

	bool GPUmalloc(const Img& srcImg);
	void GPUfree();

	~GPUcontroller();
};
