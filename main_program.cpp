#include <opencv2/opencv.hpp>
#include <iostream>
#include "UI/UI.h"
#include "Utilities/configChecker.h"
using namespace cv;
using namespace std;

int main() {
	if (Config::isCUDAavailable() == 0) {
		cout << "CUDA is not available on this PC! Exiting...";
		return 0;
	}
	UI mainInterface;
	mainInterface.UIHandler();
	return 0;
}