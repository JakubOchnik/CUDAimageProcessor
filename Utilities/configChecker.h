#pragma once
#ifdef __linux__ 
//linux code TODO
#elif _WIN32
#include<windows.h>
#else

#endif

#include <iostream>
#include "GPUinfo.h"

class Config {
public:
	static bool checkConfig();
	bool isCUDAavailableLinux(); //TODO
	static bool isCUDAavailableWin();
};