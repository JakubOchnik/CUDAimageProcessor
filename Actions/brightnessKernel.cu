#include "brightnessKernel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void calculateBrightness(unsigned char* image, int channels, int width, int height, int shift);

void executeBrightnessKernel(Img* image, int shift) {
	dim3 grid(image->getResolutionW(), image->getResolutionH());
	int channels = image->getChannelNum();
	int width = image->getResolutionW();
	int height = image->getResolutionH();
	calculateBrightness<<<grid, 1>>>(image->getImg()->data, channels, width, height, shift);
	cudaDeviceSynchronize();
	printf("");
}

__global__ void calculateBrightness(unsigned char* image, int channels, int width, int height, int shift) {
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++) {
		image[index + i] += shift;
		int outputPixel = (int)image[index + i] + shift;
		// clipping:

		if (outputPixel > 255)
			image[index + i] = 255;
		else if (outputPixel < 0)
			image[index + i] = 0;
		else
			image[index + i] = (char)outputPixel;
	}
}