#include "UI.h"

UI::UI()
{
	quit = false;
	menu = true;
	loaded = false;
	master = MainHandler();
	std::string title = baseWindowName;
#ifdef _WIN32
	SetConsoleTitle(TEXT(title.c_str()));
#else
	std::cout << "\033]0;" << title << "\007";
#endif
}

void UI::uiHandler()
{
	// Main loop
	while (!quit)
	{
		draw();
		std::getline(std::cin, inputBuffer);
		keystrokeHandler();
	}
}

void UI::draw()
{
	using namespace std;
	// clear screen
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[1;1H";
#endif
	// show menu and set window name
	if (menu)
	{
		cout << menuText << '\n' << textSeparator << '\n';
		if (loaded)
		{
			cout << "Target image info: " << '\n'
				<< pathText << master.getDstImg()->getPath() << '\n'
				<< infoResolution << " "
				<< master.getDstImg()->getResolutionW() << " x " << master.getDstImg()->getResolutionH() << '\n'
				<< infoChannels << " " << master.getDstImg()->getChannelNum() << '\n';
#ifdef _WIN32
			string title = master.getDstImg()->getPath() + " - " + baseWindowName;
			SetConsoleTitle(TEXT(title.c_str()));
#else
			cout << "\033]0;" << title << "\007";
#endif
		}
		else
		{
			cout << notLoaded << '\n';
		}
		if (!eventQueue.empty())
		{
			cout << textSeparator << '\n'
				<< "Notifications: " << '\n'
				<< printEvents();
		}
		cout << textSeparator << '\n'
			<< prompt;
	}
}


// TODO: Make this function shorter, possibly split into smaller ones
void UI::keystrokeHandler()
{
	try
	{
		using namespace std;
		// GET THE COMMAND NAME FROM THE INPUT STRING
		auto command = inputBuffer.substr(0, inputBuffer.find(' '));
		// QUIT

		// check if the command involves editing an image. If so, get img pointer and GPU handle
		std::set<std::string> val = { "quit", "load", "undo", "redo", "show", "show", "clear", "save", "history" };
		Img* dstImg;
		GPUcontroller* gpuControl;
		event result;
		if (val.find(command) == val.end())
		{
			dstImg = master.getDstImg();
			gpuControl = master.getGPUController();
		}

		if (command == "quit")
		{
			quit = true;
		}

		if (command == "load")
		{
			if (inputBuffer.length() < 5)
			{
				throw commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2)
			{
				throw commandFail;
			}
			cout << imgLoading << '\n';
			if (master.updateSrcImg(path, 1))
			{
				eventQueue.push_back(openSuccess);
				master.getHistory()->clear();
				loaded = true;
				return;
			}
			throw openFail;
		}
		if (command == "undo")
		{
			master.actionUndo();
		}
		else if (command == "redo")
		{
			master.actionRedo();
		}
		else if (command == "show")
		{
			int scale = 0;
			if (inputBuffer.find(' ') != string::npos)
			{
				auto value = inputBuffer.substr(inputBuffer.find(' '));
				value.erase(0, 1);
				scale = stoi(value);
			}

			showPreview(scale);
		}
		else if (command == "clear")
		{
			clearEvents();
		}
		else if (command == "save")
		{
			if (inputBuffer.length() < 5)
			{
				throw commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2)
			{
				throw commandFail;
			}
			if (master.imgSave(path))
			{
				eventQueue.push_back(saveSuccess);
			}
			else
			{
				throw saveFail;
			}
		}
		else if (command == "history")
		{
			editHistoryScreen();
		}
		else if (command == "help")
		{
			helpScreen();
		}
		else if (command == "crop")
		{
			if (inputBuffer.length() < 5)
			{
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			result = ActionHandler::actionSelector(crop, dstImg, value, gpuControl);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory(value, crop);
		}
		else if (command == "resize")
		{
			if (inputBuffer.length() < 6)
			{
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			result = ActionHandler::actionSelector(resize, dstImg, value, gpuControl);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory(value, resize);
		}
		else if (command == "brightness")
		{
			if (inputBuffer.length() < 11)
			{
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			result = ActionHandler::actionSelector(brightness, dstImg, value, gpuControl);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory(value, brightness);

		}
		else if (command == "invert")
		{
			result = ActionHandler::actionSelector(invertion, dstImg, "", gpuControl);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory("", invertion);
		}
		else if (command == "equalize")
		{
			result = ActionHandler::actionSelector(equalization, dstImg, "", gpuControl, true);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory("", equalization);
		}
		else if (command == "contrast")
		{
			if (inputBuffer.length() < 8)
			{
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			result = ActionHandler::actionSelector(contrast, dstImg, value, gpuControl);
			if (result == actionFail || result == parameterFail || result == noImage)
			{
				throw result;
			}
			master.addToHistory(value, contrast);
		}
		else if (command == "lut")
		{
			result = ActionHandler::actionSelector(lut3d, dstImg, "", gpuControl);
		}
		else
		{
			throw commandFail;
		}
	}
	catch (event e)
	{
		eventQueue.push_back(e);
	}
}

std::string UI::printEvents() const
{
	std::string out;
	for (auto i : eventQueue)
	{
		out += eventPrompts[i];
		out += "\n";
	}
	return out;
}

void UI::clearEvents()
{
	eventQueue.clear();
}

void UI::editHistoryScreen()
{
	using namespace std;
#ifdef _WIN32
	system("cls");
#else
	cout << "\033[2J\033[1;1H";
#endif
	cout << "-- EDIT HISTORY -- " << '\n';
	if (master.getHistory()->empty())
	{
		cout << "History is empty." << '\n';
	}
	int i = 1;
	for (const auto& userAction : *master.getHistory())
	{
		cout << "[" << i << "] " << actionNames[userAction.actionType] << " " << userAction.value << '\n';
		i++;
	}
	cout << "Press any key to return to main menu...";
	cin.get();
	draw();
}

void UI::helpScreen()
{
	using namespace std;
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[1;1H";
#endif
	cout << helpText << '\n'
		<< "Press ENTER to return to main menu...";
	cin.get();
	draw();
}

std::tuple<int, int> UI::customScale(cv::Mat& inputImage, unsigned int scale)
{
	const unsigned int width = master.getDstImg()->getResolutionW() * scale / 100;
	const unsigned int height = master.getDstImg()->getResolutionH() * scale / 100;
	cv::resize(*master.getDstImg()->getImg(), inputImage, cv::Size(width, height));
	return { width, height };
}

std::tuple<int, int, float> UI::autoScale(cv::Mat& inputImage, const std::tuple<int, int>& origSize,
	const std::tuple<int, int>& screenSize)
{
	int x, y, width, height;
	std::tie(x, y) = screenSize;
	std::tie(width, height) = origSize;
	bool changed = false;
	if (height > 0.8f * y)
	{
		height = 0.8f * y;
		width = (static_cast<float>(master.getDstImg()->getResolutionW()) * 0.8f * y) / master.getDstImg()->
			getResolutionH();
		changed = true;
	}

	if (width > 0.95f * x)
	{
		width = 0.95f * x;
		height = (master.getDstImg()->getResolutionH() * 0.95f * x) / master.getDstImg()->getResolutionH();
		changed = true;
	}
	float newScale = 0.0f;
	if (changed)
	{
		cv::resize(*master.getDstImg()->getImg(), inputImage, cv::Size(width, height));
		newScale = static_cast<float>(width) / master.getDstImg()->getResolutionW() * 100;
	}

	return { width, height, newScale };
}

void UI::showPreview(unsigned int scale)
{
	using namespace std;
	if (!master.getDstImg()->getStatus())
	{
		throw noImage;
	}
	string windowName = master.getDstImg()->getPath() +
		" (" + to_string(master.getDstImg()->getResolutionW()) + "x" +
		to_string(master.getDstImg()->getResolutionH()) + ")";
	cout << "Press any key to close the window...";
	// scale the image to fit to a current monitor height
	cv::Mat tempImg;

	// scale = 0 -> auto scaling; scale != 0 -> custom scale factor
	if (scale == 0)
	{
		int x, y;
		int height = master.getDstImg()->getResolutionH(), width = master.getDstImg()->getResolutionW();
		// max 80% of height
#ifdef _WIN32
		x = GetSystemMetrics(SM_CXSCREEN);
		y = GetSystemMetrics(SM_CYSCREEN);
#else
		Display* d = XOpenDisplay(NULL);
		Screen* s = DefaultScreenOfDisplay(d);
		x = s->width;
		y = s->height;
#endif
		const std::tuple origSize = std::make_pair(width, height);
		const std::tuple screenSize = std::make_pair(x, y);
		int newWidth, newHeight;
		float newScale;
		std::tie(newWidth, newHeight, newScale) = autoScale(tempImg, origSize, screenSize);
		if (width != newWidth || height != newHeight)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << newScale;
			const std::string s = stream.str();
			windowName = windowName + "@" + s + "%";
		}
		else
		{
			tempImg = *master.getDstImg()->getImg();
			windowName = windowName + "@100%";
		}
	}
	else
	{
		int width, height;
		std::tie(width, height) = customScale(tempImg, scale);
		windowName = windowName + "@" + to_string(scale) + "%";
	}
	windowName += (" - " + baseWindowName);
	imshow(windowName, tempImg);
	cv::waitKey(0);
	cv::destroyWindow(windowName);
}

UI::~UI() = default;
