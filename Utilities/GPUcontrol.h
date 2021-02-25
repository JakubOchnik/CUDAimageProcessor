#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MainHandler/definitions.h"
#include "../ImgHandling/ImgInfo.h"
class GPUcontroller {
private:
	bool isMemAlloc;
	bool sizeUpdate;
	unsigned char* devImgPtr;
	unsigned int memSize;
public:
	GPUcontroller();
	bool updatePtr(Img* newImg);
	bool getGPUmemStatus() const;
	bool sizeUpdateStatus() const;
	unsigned char* getImgPtr();
	bool GPUmalloc(Img* srcImg);
	void GPUfree();
	~GPUcontroller();
};