#include "contrastKernel.h"

void executeContrastKernel(Img* image, const int value, GPUcontroller* GPU)
{
	dim3 grid(image->getResolutionW(), image->getResolutionH());
	const int channels = image->getChannelNum();
	const int width = image->getResolutionW();
	const int height = image->getResolutionH();
	const size_t size = channels * width * height * sizeof(unsigned char);
	const float factor = 259 * (value + 255) / static_cast<float>(255 * (259 - value));
	calculateContrast << <grid, 1 >> > (GPU->getImgPtr(), channels, factor);
	cudaMemcpy(image->getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
}

__global__ void calculateContrast(unsigned char* image, int channels, float factor)
{
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++)
	{
		image[index + i] = truncate(factor * (image[index + i] - 128) + 128);
	}
}

__device__ unsigned char truncate(float value)
{
	if (value > 255)
		return 255;
	if (value < 0)
		return 0;
	return static_cast<unsigned char>(value);
}
