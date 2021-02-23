#include "UI.h"
using namespace std;
UI::UI() {
	quit = false;
	menu = true;
	loaded = false;
	master = mainHandler();
	std::string title = baseWindowName;
#ifdef _WIN32
	SetConsoleTitle(TEXT(title.c_str()));
#else
	std::cout << "\033]0;" << title << "\007";
#endif
}

void UI::UIHandler() {
	while (!quit) {
		draw();
		std::getline(std::cin, inputBuffer);
		keystrokeHandler();
	}
}

void UI::draw() {
	system("cls");
	if (menu) {
		std::cout << menuText << std::endl << textSeparator << std::endl;
		if (loaded) {
			std::cout << "Target image info: " << std::endl;
			std::cout << pathText << master.getDstImg()->getPath() << endl;
			std::cout << infoResolution << " " << master.getDstImg()->getResolutionW() << " x " << master.getDstImg()->getResolutionH() << std::endl;
			std::cout << infoChannels << " " << master.getDstImg()->getChannelNum() << std::endl;
			std::string title = master.getDstImg()->getPath() + " - " + baseWindowName;
#ifdef _WIN32
			SetConsoleTitle(TEXT(title.c_str()));
#else
			std::cout << "\033]0;" << title << "\007";
#endif
		}
		else {
			std::cout << notLoaded << std::endl;
		}
		if (!eventQueue.empty()) {
			cout << textSeparator << endl;
			cout << "Notifications: " << std::endl;
			cout << printEvents();
		}
		cout << textSeparator << endl;
		std::cout << prompt;
	}
}



bool UI::keystrokeHandler() {
	try {
		auto command = inputBuffer.substr(0, inputBuffer.find(' '));
		if (command == "quit") {
			quit = true;
		}
		else if (command == "load") {
			if (inputBuffer.length() < 5) {
				throw commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2) {
				throw commandFail;
			}
			cout << imgLoading << endl;
			if (master.updateSrcImg(path, 1)) {
				eventQueue.push_back(openSuccess);
				master.getHistory()->clear();
				loaded = true;
				return true;
			}
			else {
				throw openFail;
			}
		}
		else if (command == "undo") {
			if(!master.actionUndo())
				throw undoFail;
		}
		else if (command == "redo") {
			if(!master.actionRedo())
				throw redoFail;
		}
		else if (command == "show") {
			int scale = 0;
			if (inputBuffer.find(' ') != string::npos) {
				auto value = inputBuffer.substr(inputBuffer.find(' '));
				value.erase(0, 1);
				scale = stoi(value);
			}

			if (!showPreview(scale)) {
				throw noImage;
			}
		}
		else if (command == "clear") {
			clearEvents();
		}
		else if (command == "save") {
			if (inputBuffer.length() < 5) {
				throw commandFail;
			}
			auto path = inputBuffer.substr(inputBuffer.find(' '));
			path.erase(0, 1);
			if (path == inputBuffer || path.length() < 2) {
				throw commandFail;
			}
			if (master.imgSave(path)) {
				eventQueue.push_back(saveSuccess);
				return true;
			}
			else {
				throw saveFail;
			}
		}
		else if (command == "history") {
			editHistoryScreen();
		}
		else if (command == "help") {
			helpScreen();
		}
		else if (command == "crop") {
			if (inputBuffer.length() < 5) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(crop, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,crop });
		}
		else if (command == "resize") {
			if (inputBuffer.length() < 6) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(resize, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,resize });
		}
		else if (command == "brightness") {
			if (inputBuffer.length() < 11) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(brightness, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,brightness });
		}
		else if (command == "invert") {
			//auto value = inputBuffer.substr(inputBuffer.find(' '));
			//value.erase(0, 1);
			event error = actionHandler::actionSelector(invertion, master.getDstImg(), "", master.getGPUController());
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ "",invertion });
		}
		else if (command == "equalize") {
			//auto value = inputBuffer.substr(inputBuffer.find(' '));
			//value.erase(0, 1);
			event error = actionHandler::actionSelector(equalization, master.getDstImg(), "", master.getGPUController(),true);
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ "",equalization });
		}
		else if (command == "contrast") {
			if (inputBuffer.length() < 8) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(contrast, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail || error == noImage) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,contrast });
		}
		else {
			throw commandFail;
		}
		return true;
	}
	catch (event e) {
		eventQueue.push_back(e);
	}
}

std::string UI::printEvents() {
	std::string out;
	for (auto i : eventQueue) {
		out += eventPrompts[i];
		out += "\n";
	}
	return out;
}

void UI::clearEvents() {
	eventQueue.clear();
}

void UI::editHistoryScreen() {
	system("cls");
	cout << "-- EDITS HISTORY -- " << endl;
	if(master.getHistory()->empty()){
		cout << "History is empty." << endl;;
	}
	int i = 1;
	for (auto userAction : *master.getHistory()) {
		cout << "[" << i << "] " << actionNames[userAction.actionType] << " " << userAction.value << std::endl;
		i++;
	}
	cout << "Press any key to return to main menu...";
	cin.get();
	draw();
	return;
}

void UI::helpScreen() {
	system("cls");
	cout << helpText << endl;
	cout << "Press ENTER to return to main menu...";
	cin.get();
	draw();
	return;
}

bool UI::showPreview(unsigned int scale) {
	if (!master.getDstImg()->getStatus())
		return false;
	string windowName = master.getDstImg()->getPath() + " (" + to_string(master.getDstImg()->getResolutionW()) + "x" + to_string(master.getDstImg()->getResolutionH()) + ")";
	cout << "Press any key to close the window...";
	// image scaling to fit on a current monitor
	cv::Mat tempImg;
	
	if (scale == 0) {
		unsigned int x=0, y=0;
		unsigned int height = master.getDstImg()->getResolutionH(), width = master.getDstImg()->getResolutionW();
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
		bool changed = false;
		float newScale;
		if (height > 0.8*y) {

			height = 0.8 * y;
			width = (master.getDstImg()->getResolutionW() * 0.8 * y) / master.getDstImg()->getResolutionH();
			changed = true;
		}

		if (width > 0.95 * x) {
			width = 0.95 * x;
			height = (master.getDstImg()->getResolutionH() * 0.95 * x) / master.getDstImg()->getResolutionH();
			changed = true;
		}
		if (changed) {
			cv::resize(*master.getDstImg()->getImg(), tempImg, cv::Size(width, height));
			newScale = (float)width / master.getDstImg()->getResolutionW() * 100;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(2) << newScale;
			std::string s = stream.str();
			windowName = windowName + "@" + s + "%";
		}
		else {
			tempImg = *master.getDstImg()->getImg();
			windowName = windowName + "@100%";
		}
	}
	else {
		unsigned int width = master.getDstImg()->getResolutionW() * scale/100;
		unsigned int height = master.getDstImg()->getResolutionH()*scale/100;
		cv::resize(*master.getDstImg()->getImg(), tempImg, cv::Size(width, height));
		windowName = windowName + "@"+ to_string(scale) +"%";
	}
	windowName += (" - " + baseWindowName);
	cv::imshow(windowName, tempImg);
	cv::waitKey(0);
	cv::destroyWindow(windowName);
	return true;
}

UI::~UI() {

}