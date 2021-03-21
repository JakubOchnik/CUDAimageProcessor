#include "UI/UI.h"
#include "Utilities/configChecker.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main()
{
	if (Config::isCUDAavailable() == 0)
	{
		cout << "CUDA is not available on this PC! Exiting...";
#ifdef _WIN32
		Sleep(5 * 1000);
#else
		usleep(5 * 1000000);
#endif
		return 0;
	}
	UI mainInterface;
	mainInterface.UIHandler();
	return 0;
}