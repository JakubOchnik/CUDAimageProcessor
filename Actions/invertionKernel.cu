#include "invertionKernel.h"


void executeInvertionKernel(Img* image, GPUcontroller* GPU) {
	dim3 grid(image->getResolutionW(), image->getResolutionH());
	int channels = image->getChannelNum();
	int width = image->getResolutionW();
	int height = image->getResolutionH();
	size_t size = channels * width * height * sizeof(unsigned char);
	invertImage << <grid, 1 >> > (GPU->getImgPtr(), channels);
	cudaMemcpy(image->getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
}

__global__ void invertImage(unsigned char* image, int channels) {
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++)
		image[index + i] = 255 - image[index + i];
}