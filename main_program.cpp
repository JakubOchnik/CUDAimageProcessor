#include <opencv2/opencv.hpp>
#include <iostream>
#include <UI/Program.hpp>
#include <Utilities/ConfigChecker.hpp>

int main(int argc, char* argv[])
{
	if (Config::checkConfig() == false)
	{
		std::cout << "CUDA is not available on this PC! Press ENTER to exit...";
		std::cin.get();
		return 0;
	}

	bool enableGpu{true};

	ProgramHandler prog(enableGpu);
	prog.run();
	return 0;
}
