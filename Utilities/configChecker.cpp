#include "configChecker.h"

bool Config::isCUDAavailableWin() {
	if (LoadLibraryA("nvcuda.dll") != nullptr) {
		GPUinfo::loadGPUinfo();
	}
	return 1;
}

bool Config::checkConfig() {
#ifdef __linux__ 
	//TODO
#elif _WIN32
	return isCUDAavailableWin();
#else
	return 0;
#endif
}

bool Config::isCUDAavailableLinux()
{
	//TODO
	return false;
}
