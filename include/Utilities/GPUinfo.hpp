#pragma once
#include <cuda_runtime.h>
#include <iostream>
#include <tuple>

class GpuInfo
{
public:
	static std::tuple<int, int> getMaxDimensions();
	static void					showGpuInfo();
	static bool					isCompatible();
};
