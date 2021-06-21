#include <opencv2/opencv.hpp>
#include <iostream>
#include "UI/Ui.h"
#include "Utilities/configChecker.h"

int main(int argc, char* argv[])
{
	if (Config::checkConfig() == false)
	{
		std::cout << "CUDA is not available on this PC! Press ENTER to exit...";
		std::cin.get();
		return 0;
	}

	Ui mainInterface;
	mainInterface.uiHandler();
	return 0;
}
