#include <Utilities/GPUinfo.hpp>

bool GpuInfo::isCompatible()
{
	cudaDeviceProp prop;
	int devCount = 0;
	cudaGetDeviceCount(&devCount);
	if (devCount < 1 || cudaGetDeviceProperties(&prop, 0) != cudaSuccess)
	{
		return false;
	}
	return true;
}

std::tuple<int, int> GpuInfo::getMaxDimensions()
{
	cudaDeviceProp prop;
	int devCount{};
	cudaGetDeviceCount(&devCount);
	if (devCount < 1)
	{
		return { -1, -1 };
	}
	if (cudaGetDeviceProperties(&prop, 0) != cudaSuccess)
	{
		return { -1, -1 };
	}
	// INT_MAX x 65535 in compute capability 3.x+
	// 65535 x 65535 in previous compute capabilities
	return { prop.maxGridSize[0], prop.maxGridSize[1] };
}

void GpuInfo::showGpuInfo()
{
	using namespace std;
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, 0);
	std::tuple<int, int> maxDims = getMaxDimensions();
	cout << "CUDA IMAGE PROCESSOR\nJakub Ochnik 2021\n------------------------------\n"
		<< "GPU device info: \n"
		<< "Name: " << prop.name << "\n"
		<< "Compute capability: " << prop.major << "." << prop.minor << "\n"
		<< "Total global memory: " << prop.totalGlobalMem / (1024 * 1024) << " MB" << "\n"
		<< "Max supported image size: " << std::get<0>(maxDims) << " x " << std::get<1>(maxDims) << "\n"
		<< "Press any key to start...";
	cin.get();
}
