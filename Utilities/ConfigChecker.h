#pragma once
#include "GpuInfo.h"

#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

class Config
{
public:
	static bool checkConfig();
	static bool isCUDActive();
};
