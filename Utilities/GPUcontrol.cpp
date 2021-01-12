#include "GPUcontrol.h"


GPUcontroller::GPUcontroller() {
	isMemAlloc = false;
	imgPtr = nullptr;
}

bool GPUcontroller::getGPUmemStatus() const {
	return isMemAlloc;
}
bool GPUcontroller::GPUmalloc(Img srcImg) {
	if (isMemAlloc == true) {
		return 0;
	}
	unsigned char* img = srcImg.getImg()->data;
	size_t dataSize = srcImg.getResolutionH() * srcImg.getResolutionW() * srcImg.getChannelNum() * sizeof(unsigned char);
	if (cudaMallocManaged((void**)img, dataSize) != cudaSuccess) {
		imgPtr = nullptr;
		return 0;
	}
	else {
		imgPtr = srcImg.getImg()->data;
		int device = -1;
		cudaGetDevice(&device);
		cudaMemPrefetchAsync(img, dataSize, device, nullptr);
		return 1;
	}
}

void GPUcontroller::GPUfree() {
	cudaDeviceSynchronize();
	cudaFree(imgPtr);
}

void GPUcontroller::updatePtr(unsigned char* newImg) {
	imgPtr = newImg;
}

unsigned char* GPUcontroller::getImgPtr() {
	return imgPtr;
}