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

void GPUinfo::showGPUinfo(cudaDeviceProp prop) {
	cout << "GPU device info:" << endl;
	cout << "Name: " << prop.name << endl;
	cout << "Compute capability: " << prop.major << prop.minor << endl;
	cout << "Total global memory: " << prop.totalGlobalMem << " bytes" << endl;
	cout << "Press any key to start...";
	cin.get();
}
