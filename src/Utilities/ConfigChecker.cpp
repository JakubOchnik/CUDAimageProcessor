#include <Utilities/ConfigChecker.hpp>

bool Config::isCUDActive()
{
	// check CUDA driver availability
#ifdef _WIN32
	if (LoadLibraryA("nvcuda.dll") == nullptr)
	{
		return false;
	}
#else
	if (dlopen("libcuda.so", RTLD_NOW) == nullptr)
	{
		return false;
	}
#endif
	// if CUDA driver is available, proceed to checking if the GPU is compatible
	if (!GpuInfo::isCompatible())
	{
		return false;
	}
	return true;
}

bool Config::checkConfig()
{
	if (isCUDActive() == false)
	{
		return false;
	}
	GpuInfo::showGpuInfo();
	return true;
}
