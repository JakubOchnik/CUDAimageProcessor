#include <Consts/Errors.hpp>
#include <Consts/GenericEvents.hpp>
#include <Events/EventHistory.hpp>
#include <Events/History.hpp>
#include <ImgHandling/ImgInfo.hpp>
#include <MainHandler/MainHandler.hpp>
#include <UI/UIdefinitions.hpp>
#include <UI/ui.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <tuple>

#ifdef _WIN32
#include <windows.h>
#else
#include <X11/Xlib.h>
#endif

void ui::setWindowName(const std::string& newName)
{
#ifdef _WIN32
	SetConsoleTitle(TEXT(newName.c_str()));
#else
	std::cout << "\033]0;" << newName << "\007";
#endif
}

void ui::clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	std::cout << "\033[2J\033[1;1H";
#endif
}

void ui::draw(const Img& dstImg, const EventHistory& events, bool loaded)
{
	using namespace std;
	using namespace consts::ui;
	clearScreen();
	// show menu and set window name

	cout << HEADER_TEXT << '\n' << SEPARATOR_TEXT << '\n';
	if (loaded)
	{
		cout << "Target image info: " << '\n'
			 << FILEPATH_TEXT << dstImg.getPath() << '\n'
			 << RESOLUTION_TEXT << " " << dstImg.getResolutionW() << " x "
			 << dstImg.getResolutionH() << '\n'
			 << CHANNELS_TEXT << " " << dstImg.getChannelNum() << '\n';
		const string title = dstImg.getPath() + " - " + BASE_WINDOW_NAME;
		setWindowName(title);
	}
	else
	{
		cout << NOT_LOADED_TEXT << '\n';
	}
	if (!events.isEmpty())
	{
		cout << SEPARATOR_TEXT << '\n'
			 << "Notifications: " << '\n'
			 << events.getEvents();
	}
	cout << SEPARATOR_TEXT << '\n' << PROMPT_TEXT;
}

void ui::editHistoryScreen(const History& history)
{
	using namespace std;
	clearScreen();
	cout << history.getFormattedHistory() << "\n";
	cout << "Press any key to return to main menu...";
	cin.get();
}

void ui::helpScreen()
{
	using namespace std;
	using namespace consts::ui;
	clearScreen();
	cout << HELP_TEXT_CONTENT << '\n'
		 << "Press ENTER to return to main menu...";
	cin.get();
}

std::tuple<int, int>
ui::customScale(cv::Mat& inputImage, Img& dstImg, unsigned int scale)
{
	const unsigned int width{dstImg.getResolutionW() * scale / 100};
	const unsigned int height{dstImg.getResolutionH() * scale / 100};
	resize(dstImg.getImg(), inputImage, cv::Size(width, height));
	return {width, height};
}

std::tuple<int, int, float> ui::autoScale(cv::Mat& inputImage,
										  Img&	   dstImg,
										  const std::tuple<int, int>& origSize,
										  const std::tuple<int, int>& screenSize)
{
	int x, y, width, height;
	std::tie(x, y)			= screenSize;
	std::tie(width, height) = origSize;
	bool changed			= false;
	if (height > 0.8f * y)
	{
		height = 0.8f * y;
		width  = (static_cast<float>(dstImg.getResolutionW()) * 0.8f * y)
				/ dstImg.getResolutionH();
		changed = true;
	}

	if (width > 0.95f * x)
	{
		width  = 0.95f * x;
		height = (dstImg.getResolutionH() * 0.95f * x) / dstImg.getResolutionH();
		changed = true;
	}
	float newScale = 0.0f;
	if (changed)
	{
		resize(dstImg.getImg(), inputImage, cv::Size(width, height));
		newScale = static_cast<float>(width) / dstImg.getResolutionW() * 100;
	}

	return {width, height, newScale};
}

void ui::showPreview(Img& dstImg, unsigned int scale)
{
	using namespace std;
	using namespace consts::ui;

	if (!dstImg.getStatus())
	{
		throw event::error::NotLoadedFail();
	}
	string windowName = dstImg.getPath() + " ("
						+ to_string(dstImg.getResolutionW()) + "x"
						+ to_string(dstImg.getResolutionH()) + ")";
	cout << "Press any key to close the window...";
	// scale the image to fit to a current monitor height
	cv::Mat tempImg;

	// scale = 0 -> auto scaling; scale != 0 -> custom scale factor
	if (scale == 0)
	{
		int x, y;
		int height = dstImg.getResolutionH(), width = dstImg.getResolutionW();
		// max 80% of height
#ifdef _WIN32
		x = GetSystemMetrics(SM_CXSCREEN);
		y = GetSystemMetrics(SM_CYSCREEN);
#else
		Display* d = XOpenDisplay(NULL);
		Screen*	 s = DefaultScreenOfDisplay(d);
		x		   = s->width;
		y		   = s->height;
#endif
		const std::tuple origSize{std::make_pair(width, height)};
		const std::tuple screenSize{std::make_pair(x, y)};
		int				 newWidth, newHeight;
		float			 newScale;
		std::tie(newWidth, newHeight, newScale) =
			autoScale(tempImg, dstImg, origSize, screenSize);
		if (width != newWidth || height != newHeight)
		{
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << newScale;
			const std::string s = stream.str();
			windowName			= windowName + "@" + s + "%";
		}
		else
		{
			tempImg	   = dstImg.getImg();
			windowName = windowName + "@100%";
		}
	}
	else
	{
		int width, height;
		std::tie(width, height) = customScale(tempImg, dstImg, scale);
		windowName				= windowName + "@" + to_string(scale) + "%";
	}
	windowName += (" - " + std::string(BASE_WINDOW_NAME));
	imshow(windowName, tempImg);
	cv::waitKey(0);
	cv::destroyWindow(windowName);
	cv::waitKey(1);
}

void ui::printString(const std::string& output)
{
	std::cout << output;
}