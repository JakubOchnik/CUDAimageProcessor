#include <Commands/GpuImg/Kernels/BrightnessKernel.cuh>

void executeBrightnessKernel(Img &image, const int shift, GPUcontroller *GPU)
{
	dim3 grid(image.getResolutionW(), image.getResolutionH());
	const int channels = image.getChannelNum();
	const int width = image.getResolutionW();
	const int height = image.getResolutionH();
	const size_t size = channels * width * height * sizeof(unsigned char);
	calculateBrightness<<<grid, 1>>>(image.getImg()->data, channels, shift);

	//cudaMemcpy(image.getImg()->data, GPU->getImgPtr(), size, cudaMemcpyDeviceToHost);
}

__global__ void calculateBrightness(unsigned char *image, int channels, int shift)
{
	int x = blockIdx.x;
	int y = blockIdx.y;

	int index = (x + y * gridDim.x) * channels;

	for (int i = 0; i < channels; i++)
	{
		int outputPixel = image[index + i] + shift;
		if (outputPixel > 255)
			image[index + i] = 255;
		else if (outputPixel < 0)
			image[index + i] = 0;
		else
			image[index + i] = static_cast<char>(outputPixel);
	}
}
