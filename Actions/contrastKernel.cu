#include "contrastKernel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void calculateContrast(unsigned char* image, int channels, float factor);
__device__ unsigned char truncate(float value);
void executeContrastKernel(Img* image, int value, GPUcontroller* GPU) {
	dim3 grid(image->getResolutionW(), image->getResolutionH());
	int channels = image->getChannelNum();
	int width = image->getResolutionW();
	int height = image->getResolutionH();
	size_t size = channels * width * height * sizeof(unsigned char);
	float factor = (259 * (value + 255)) / (float)(255 * (259 - value));
	calculateContrast <<<grid, 1 >>> (GPU->getImgPtr(), channels, factor);
	cudaMemcpy(image->getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
}

__global__ void calculateContrast(unsigned char* image, int channels, float factor) {
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++) {
		image[index+i] = truncate(factor*(image[index + i]-128)+128);
	}
}

__device__ unsigned char truncate(float value) {
	if (value > 255)
		return 255;
	else if (value < 0)
		return 0;
	return (unsigned char)value;
}