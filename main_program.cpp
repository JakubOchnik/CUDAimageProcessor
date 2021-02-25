#include <opencv2/opencv.hpp>
#include <iostream>
#include "UI/UI.h"
#include "Utilities/configChecker.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using namespace cv;
using namespace std;

int main() {
	if (Config::isCUDAavailable() == 0) {
		cout << "CUDA is not available on this PC! Exiting...";
#ifdef _WIN32
		Sleep(5000);
#else
		unsigned int microsecond = 1000000;
		usleep(5 * microsecond);//sleeps for 3 second
#endif
		return 0;
	}
	UI mainInterface;
	mainInterface.UIHandler();
	return 0;
}