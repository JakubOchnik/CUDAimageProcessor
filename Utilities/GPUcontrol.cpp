#include "GPUcontrol.h"

GPUcontroller::GPUcontroller() {
	isMemAlloc = false;
	sizeUpdate = false;
	devImgPtr = nullptr;
}

bool GPUcontroller::sizeUpdateStatus() const {
	return sizeUpdate;
}

bool GPUcontroller::getGPUmemStatus() const {
	return isMemAlloc;
}
bool GPUcontroller::GPUmalloc(Img* srcImg) {
	if (isMemAlloc == true) {
		return 0;
	}
	//unsigned char* img = srcImg->getImg()->data;
	size_t dataSize = srcImg->getResolutionH() * srcImg->getResolutionW() * srcImg->getChannelNum() * sizeof(unsigned char);
	//unsigned char* temp = (unsigned char*)malloc(dataSize); // DIRTY FIX, TODO
	// devImgPtr - wskaznik dev
	if (cudaMalloc((void**)&devImgPtr, dataSize) != cudaSuccess) {
		devImgPtr = nullptr;
		return 0;
	}
	else {
		// devImgPtr is allocated
		cudaMemcpy(devImgPtr, srcImg->getImg()->data, dataSize,cudaMemcpyHostToDevice);
		isMemAlloc = true;
		sizeUpdate = false;
		return 1;
	}
	/*memcpy(temp, img, dataSize);
	if (cudaMallocManaged((void**)&img, dataSize) != cudaSuccess) {
		imgPtr = nullptr;
		return 0;
	}
	else {
		imgPtr = img;
		memcpy(img, temp, dataSize);
		free(temp);
		int device = -1;
		cudaGetDevice(&device);
		cudaMemPrefetchAsync(img, dataSize, device, nullptr);
		return 1;
	}*/
}

void GPUcontroller::GPUfree() {
	//cudaDeviceSynchronize();
	cudaFree(devImgPtr);
}

void GPUcontroller::updatePtr(Img* newImg) {
	size_t newSize = newImg->getResolutionH() * newImg->getResolutionW() * newImg->getChannelNum() * sizeof(unsigned char);
	cudaMemcpy(devImgPtr, newImg->getImg()->data, newSize, cudaMemcpyDeviceToHost);
}

unsigned char* GPUcontroller::getImgPtr() {
	return devImgPtr;
}