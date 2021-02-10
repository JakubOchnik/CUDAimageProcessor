#include "configChecker.h"

bool Config::isCUDAavailable() {
#ifdef _WIN32
	if (LoadLibraryA("nvcuda.dll") == nullptr) {
		return 0;
	}
#else
	if (dlopen("libcuda.so", RTLD_NOW) == nullptr) {
		return 0;
	}
#endif
	if (GPUinfo::loadGPUinfo())
		return 1;
	return 0;
}