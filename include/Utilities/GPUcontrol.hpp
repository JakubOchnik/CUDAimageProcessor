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

	unsigned char* getImgPtr();
	bool		   getGPUmemStatus() const;
	bool		   sizeUpdateStatus() const;

	bool updatePtr(Img* newImg);

	bool GPUmalloc(Img* srcImg);
	void GPUfree();

	~GPUcontroller();
};
