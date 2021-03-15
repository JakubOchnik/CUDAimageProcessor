#pragma once

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <tuple>
#include <stdlib.h>
#include <iostream>
using namespace std;

class GPUinfo {
public:
	static std::tuple<int, int> getMaxDimensions();
	static bool loadGPUinfo();
	static void showGPUinfo(cudaDeviceProp prop);
};