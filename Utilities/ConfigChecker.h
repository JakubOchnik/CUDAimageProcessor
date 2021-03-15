#pragma once
#include "GPUinfo.h"

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class Config {
public:
	static bool isCUDAavailable();
};