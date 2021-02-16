#include "GPUinfo.h"

bool GPUinfo::loadGPUinfo() {
	cudaDeviceProp prop;
	int devCount = 0;
	cudaGetDeviceCount(&devCount);
	if (devCount < 1) {
		return 0;
	}
	if(cudaGetDeviceProperties(&prop, 0)!=cudaSuccess)
		return 0;
	showGPUinfo(prop);
	return 1;
}

std::tuple<int, int> GPUinfo::getMaxDimensions() {
	cudaDeviceProp prop;
	int devCount = 0;
	cudaGetDeviceCount(&devCount);
	if (devCount < 1) {
		return { -1, -1 };
	}
	if (cudaGetDeviceProperties(&prop, 0) != cudaSuccess)
		return { -1,-1 };
	if (prop.major >= 3) {
		return { INT_MAX,65535 };
	}
	else {
		return { 65535, 65535 };

	}
}

void GPUinfo::showGPUinfo(cudaDeviceProp prop) {
	cout << "CUDA IMAGE PROCESSOR\nJakub Ochnik 2021\n------------------------------\n";
	cout << "GPU device info:" << endl;
	cout << "Name: " << prop.name << endl;
	cout << "Compute capability: " << prop.major <<"."<< prop.minor << endl;
	cout << "Total global memory: " << prop.totalGlobalMem/(1024*1024) << " MB" << endl;
	cout << "Press any key to start...";
	cin.get();
}
