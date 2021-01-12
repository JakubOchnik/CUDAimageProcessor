#pragma once
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "../MainHandler/definitions.h"
#include "../ImgHandling/ImgInfo.h"
class GPUcontroller {
private:
	bool isMemAlloc;
	unsigned char* imgPtr;
public:
	GPUcontroller();
	void updatePtr(unsigned char* newPtr);
	bool getGPUmemStatus() const;
	unsigned char* getImgPtr();
	bool GPUmalloc(Img srcImg);
	void GPUfree();
};