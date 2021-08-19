#include "Program.hpp"

void ProgramHandler::run()
{
	ui::setWindowName(BASE_WINDOW_NAME);
	// Main loop
	while (!master.isQuit())
	{
		ui::draw(master.getDstImg(), master.getEvents(), master.isLoaded());
		std::getline(std::cin, inputBuffer);
		keystrokeHandler(master);
	}
}

void ProgramHandler::keystrokeHandler(MainHandler& master)
{
	using namespace std;
	// GET THE COMMAND NAME FROM THE INPUT STRING
	const auto command = inputBuffer.substr(0, inputBuffer.find(' '));
	// check if the command involves editing an image. If so, get img pointer and GPU handle
	std::set<std::string> val = { "quit", "load", "undo", "redo", "show", "show", "clear", "save", "history" };
	Img* dstImg;
	GPUcontroller* gpuControl;

	if (val.find(command) == val.end())
	{
		//dstImg = master.getDstImg();
		//gpuControl = master.getGPUController();
	}

	// execute the command

}
