#include <Commands/GpuImg/Kernels/EqualizationKernel.cuh>

bool executeEqualizationKernel(Img& image, GPUcontroller* GPU)
{
	const unsigned int channels = image.getChannelNum();
	const unsigned int width = image.getResolutionW();
	const unsigned int height = image.getResolutionH();
	// memory allocation with error checking
	auto min = new(std::nothrow) int[channels];
	if (!min)
	{
		return false;
	}
	auto max = new(std::nothrow) int[channels];
	if (!max)
	{
		return false;
	}
	for (int i = 0; i < channels; i++)
	{
		min[i] = 255;
		max[i] = 0;
	}
	int* devMin = nullptr;
	int* devMax = nullptr;
	cudaMalloc((void**)&devMin, channels * sizeof(int));
	cudaMalloc((void**)&devMax, channels * sizeof(int));

	cudaMemcpy(devMin, min, channels * sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(devMax, max, channels * sizeof(int), cudaMemcpyHostToDevice);

	dim3 grid(width, height);

	const size_t size = channels * width * height * sizeof(unsigned char);
	calculateEdgeBrightness << <grid, 1 >> > (GPU->getImgPtr(), channels, devMin, devMax);
	cudaMemcpy(min, devMin, channels * sizeof(int), cudaMemcpyDeviceToHost);
	cudaMemcpy(max, devMax, channels * sizeof(int), cudaMemcpyDeviceToHost);
	calculateEqualization << <grid, 1 >> > (GPU->getImgPtr(), channels, devMin, devMax);

	cudaMemcpy(image.getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
	cudaFree(devMin);
	cudaFree(devMax);
	delete[] min;
	delete[] max;
	return true;
}

__global__ void calculateEdgeBrightness(unsigned char* image, int channels, int* min, int* max)
{
	int x = blockIdx.x;
	int y = blockIdx.y;
	int imageIdx = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++)
	{
		atomicMin(&min[i], image[imageIdx + i]);
		atomicMax(&max[i], image[imageIdx + i]);
	}
}

__global__ void calculateEqualization(unsigned char* image, int channels, int* min, int* max)
{
	int x = blockIdx.x;
	int y = blockIdx.y;

	int image_idx = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++)
	{
		image[image_idx + i] = getEqualizedValue(image[image_idx + i], min[i], max[i]);
	}
}

__device__ int getEqualizedValue(unsigned char value, int min, int max)
{
	int target_min = 0;
	int target_max = 255;

	return (target_min + (value - min) * ((target_max - target_min) / (max - min)));
}
