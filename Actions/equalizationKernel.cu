#include "equalizationKernel.h"


bool executeEqualizationKernel(Img* image, GPUcontroller* GPU) {
	int channels = image->getChannelNum();
	int width = image->getResolutionW();
	int height = image->getResolutionH();
	int* min;
	int* max;
	// memory allocation with error checking
	min = new (std::nothrow) int[channels];
	if (!min) {
		return false;
	}
	max = new (std::nothrow) int[channels];
	if (!max) {
		return false;
	}
	for (int i = 0; i < channels; i++) {
		min[i] = 255;
		max[i] = 0;
	}
	int* dev_min = nullptr;
	int* dev_max = nullptr;
	cudaMalloc((void**)&dev_min, channels * sizeof(int));
	cudaMalloc((void**)&dev_max, channels * sizeof(int));

	cudaMemcpy(dev_min, min, channels * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_max, max, channels * sizeof(int), cudaMemcpyHostToDevice);

	dim3 grid(width, height);

	size_t size = channels * width * height * sizeof(unsigned char);
	calculateEdgeBrightness << <grid, 1 >> > (GPU->getImgPtr(), channels, dev_min, dev_max);
	cudaMemcpy(min, dev_min, channels * sizeof(int), cudaMemcpyDeviceToHost);
	cudaMemcpy(max, dev_max, channels * sizeof(int), cudaMemcpyDeviceToHost);
	calculateEqualization << <grid, 1 >> > (GPU->getImgPtr(), channels, dev_min, dev_max);

	cudaMemcpy(image->getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
	cudaFree(dev_min);
	cudaFree(dev_max);
	delete[] min;
	delete[] max;
	return true;
}

__global__ void calculateEdgeBrightness(unsigned char* image, int channels, int* min, int* max) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int imageIdx = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++) {
		atomicMin(&min[i], image[imageIdx + i]);
		atomicMax(&max[i], image[imageIdx + i]);
	}
}

__global__ void calculateEqualization(unsigned char* image, int channels, int* min, int* max) {
	int x = blockIdx.x;
	int y = blockIdx.y;

	int image_idx = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++) {
		image[image_idx + i] = getEqualizedValue(image[image_idx + i], min[i], max[i]);
	}
}

__device__ int getEqualizedValue(unsigned char value, int min, int max) {
	int target_min = 0;
	int target_max = 255;

	return(target_min + (value - min) * (int)((target_max - target_min) / (max - min)));
}