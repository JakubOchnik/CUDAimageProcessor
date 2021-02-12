#include "brightnessKernel.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__ void calculateBrightness(unsigned char* image, int channels, int width, int height, int shift);

void executeBrightnessKernel(Img* image, int shift, GPUcontroller* GPU) {
	dim3 grid(image->getResolutionW(), image->getResolutionH());
	int channels = image->getChannelNum();
	int width = image->getResolutionW();
	int height = image->getResolutionH();
	size_t size = channels * width * height * sizeof(unsigned char);
	calculateBrightness<<<grid, 1>>>(GPU->getImgPtr(), channels, width, height, shift);
	cudaMemcpy(image->getImg()->data, GPU->getImgPtr(),size, cudaMemcpyDeviceToHost);
	//cudaDeviceSynchronize();
	//printf("");
}

__global__ void calculateBrightness(unsigned char* image, int channels, int width, int height, int shift) {
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;
	
	for (int i = 0; i < channels; i++) {
		//image[index + i] += shift;
		int outputPixel = image[index + i] + shift;
		// debug:
		/*if (index < 100)
			printf("%d input: %d outputPixel: %d\n ", index, image[index], outputPixel);*/
		if (outputPixel > 255)
			image[index + i] = 255;
		else if (outputPixel < 0)
			image[index + i] = 0;
		else
			image[index + i] = (char)outputPixel;
	}
	// debug:
	/*if(index<100)
		printf("index %d out %d shift %d\n", index, image[index], shift);
	image[index] = 1;*/
}