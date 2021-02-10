#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <iostream>
#include "GPUinfo.h"

class Config {
public:
	static bool isCUDAavailable();
};