#pragma once
#include "cuda_runtime.h"

#include <tuple>
#include <iostream>

class GpuInfo
{
public:
	static std::tuple<int, int> getMaxDimensions();
	static void showGpuInfo();
	static bool isCompatible();
};
