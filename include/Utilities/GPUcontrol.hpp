#pragma once
#include <cuda_runtime.h>
#include <MainHandler/definitions.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <Utilities/UnifiedPtr.hpp>

class GPUcontroller
{
private:
	bool sizeUpdate;
	UnifiedPtr data;

public:
	GPUcontroller();

	UnifiedPtr &getImgPtr();
	bool getGPUmemStatus() const;
	bool sizeUpdateStatus() const;

	UnifiedPtr &createGpuPointer(unsigned char *inputData, size_t dataSize);
	bool updatePtr(Img *newImg);

	~GPUcontroller();
};
