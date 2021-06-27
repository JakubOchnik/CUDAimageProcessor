#include "Ui.h"

void Ui::uiHandler()
{
	setWindowName(BASE_WINDOW_NAME);
	// Main loop
	while (!quit)
	{
		draw();
		std::getline(std::cin, inputBuffer);
		keystrokeHandler();
	}
}

void Ui::setWindowName(const std::string& newName) const
{
#ifdef _WIN32
	SetConsoleTitle(TEXT(newName.c_str()));
#else
	cout << "\033]0;" << newName << "\007";
#endif
}

void Ui::clearScreen() const
{
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[1;1H";
#endif
}

void Ui::draw()
{
	using namespace std;
	clearScreen();
	// show menu and set window name
	if (menu)
	{
		cout << HEADER_TEXT << '\n' << SEPARATOR_TEXT << '\n';
		if (loaded)
		{
			cout << "Target image info: " << '\n'
				<< FILEPATH_TEXT << master.getDstImg()->getPath() << '\n'
				<< RESOLUTION_TEXT << " "
				<< master.getDstImg()->getResolutionW() << " x " << master.getDstImg()->getResolutionH() << '\n'
				<< CHANNELS_TEXT << " " << master.getDstImg()->getChannelNum() << '\n';
			const string title = master.getDstImg()->getPath() + " - " + BASE_WINDOW_NAME;
			setWindowName(title);
		}
		else
		{
			cout << NOT_LOADED_TEXT << '\n';
		}
		if (!eventQueue.empty())
		{
			cout << SEPARATOR_TEXT << '\n'
				<< "Notifications: " << '\n'
				<< printEvents();
		}
		cout << SEPARATOR_TEXT << '\n'
			<< PROMPT_TEXT;
	}
}


// TODO: Make this function shorter, possibly split into smaller ones
void Ui::keystrokeHandler()
{
	try
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
				throw Event::commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2)
			{
				throw Event::commandFail;
			}
			cout << FILE_LOADING_TEXT << '\n';
			if (master.updateSrcImg(path, 1))
			{
				eventQueue.push_back(Event::openSuccess);
				master.getHistory()->clear();
				loaded = true;
				return;
			}
			throw Event::openFail;
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
				throw Event::commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2)
			{
				throw Event::commandFail;
			}
			if (master.imgSave(path))
			{
				eventQueue.push_back(Event::saveSuccess);
			}
			else
			{
				throw Event::saveFail;
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
				throw Event::commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			if (const auto result = ActionHandler::actionSelector(Action::crop, dstImg, value, gpuControl);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory(value, Action::crop);
		}
		else if (command == "resize")
		{
			if (inputBuffer.length() < 6)
			{
				//throw std::exception(Event::commandFail);
				throw Event::commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			if (const auto result = ActionHandler::actionSelector(Action::resize, dstImg, value, gpuControl);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory(value, Action::resize);
		}
		else if (command == "brightness")
		{
			if (inputBuffer.length() < 11)
			{
				throw Event::commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			if (const auto result = ActionHandler::actionSelector(Action::brightness, dstImg, value, gpuControl);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory(value, Action::brightness);
		}
		else if (command == "invert")
		{
			if (const auto result = ActionHandler::actionSelector(Action::invertion, dstImg, "", gpuControl);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory("", Action::invertion);
		}
		else if (command == "equalize")
		{
			if (const auto result = ActionHandler::actionSelector(Action::equalization, dstImg, "", gpuControl, true);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory("", Action::equalization);
		}
		else if (command == "contrast")
		{
			if (inputBuffer.length() < 8)
			{
				throw Event::commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			if (const auto result = ActionHandler::actionSelector(Action::contrast, dstImg, value, gpuControl);
				isActionValid(result))
			{
				throw result;
			}
			master.addToHistory(value, Action::contrast);
		}
		else if (command == "lut")
		{
			if (const auto result = ActionHandler::actionSelector(Action::lut3d, dstImg, "", gpuControl);
				isActionValid(result))
			{
				throw result;
			}
		}
		else
		{
			throw Event::commandFail;
		}
	}
	catch (const Event& e)
	{
		eventQueue.push_back(e);
	}
}

bool Ui::isActionValid(const Event result) const
{
	return result == Event::actionFail || result == Event::parameterFail || result == Event::noImage;
}

std::string [[nodiscard]] Ui::printEvents() const
{
	std::string out;
	for (const auto& event : eventQueue)
	{
		out += EVENT_TEXT_PROMPTS.at(event);
		out += "\n";
	}
	return out;
}

void Ui::clearEvents()
{
	eventQueue.clear();
}

void Ui::addEvent(Event& e)
{
	eventQueue.push_back(e);
}

void Ui::editHistoryScreen()
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
		cout << "[" << i << "] " << ACTION_TEXT_NAMES.at(userAction.actionType) << " " << userAction.value << '\n';
		i++;
	}
	cout << "Press any key to return to main menu...";
	cin.get();
	draw();
}

void Ui::helpScreen()
{
	using namespace std;
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[1;1H";
#endif
	cout << HELP_TEXT_CONTENT << '\n'
		<< "Press ENTER to return to main menu...";
	cin.get();
	draw();
}

std::tuple<int, int> Ui::customScale(cv::Mat& inputImage, unsigned int scale)
{
	const unsigned int width = master.getDstImg()->getResolutionW() * scale / 100;
	const unsigned int height = master.getDstImg()->getResolutionH() * scale / 100;
	resize(*master.getDstImg()->getImg(), inputImage, cv::Size(width, height));
	return { width, height };
}

std::tuple<int, int, float> Ui::autoScale(cv::Mat& inputImage, const std::tuple<int, int>& origSize,
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
		resize(*master.getDstImg()->getImg(), inputImage, cv::Size(width, height));
		newScale = static_cast<float>(width) / master.getDstImg()->getResolutionW() * 100;
	}

	return { width, height, newScale };
}

void Ui::showPreview(unsigned int scale)
{
	using namespace std;
	if (!master.getDstImg()->getStatus())
	{
		throw Event::noImage;
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
	windowName += (" - " + BASE_WINDOW_NAME);
	imshow(windowName, tempImg);
	cv::waitKey(0);
	cv::destroyWindow(windowName);
}
