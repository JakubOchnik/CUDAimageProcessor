#include "UI.h"
using namespace std;
UI::UI() {
	quit = false;
	menu = true;
	loaded = false;
	menuText = "invert: invert colors\ncontrast: enhance contrast\nbrightness: enhance brightness\nhistogram: generate histogram\nequalize: histogram equalization\ncrop: crop image\n -----------------\nload: load image\nsave: save image\nhistory: view edit history\nclear: clear notifications\nquit: quit";
	infoResolution = "Image resolution:";
	infoChannels = "Image color channels:";
	prompt = "IP>";
	notLoaded = "Image not loaded";
	pathText = "File path: ";
	textSeparator = "--------------------------------------------------";
	master = mainHandler();
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
			if (master.updateSrcImg(path, 1)) {
				eventQueue.push_back(openSuccess);
				loaded = true;
				return true;
			}
			else {
				throw openFail;
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
		else if (command == "crop") {
			if (inputBuffer.length() < 5) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(crop, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,crop });
		}
		else if (command == "brightness") {
			if (inputBuffer.length() < 11) {
				throw commandFail;
			}
			auto value = inputBuffer.substr(inputBuffer.find(' '));
			value.erase(0, 1);
			event error = actionHandler::actionSelector(brightness, master.getDstImg(), value, master.getGPUController());
			if (error == actionFail || error == parameterFail) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ value,brightness });
		}
		else if (command == "invert") {
			//auto value = inputBuffer.substr(inputBuffer.find(' '));
			//value.erase(0, 1);
			event error = actionHandler::actionSelector(invertion, master.getDstImg(), "", master.getGPUController());
			if (error == actionFail || error == parameterFail) {
				throw error;
			}
			vector<edit>* ref = master.getHistory();
			ref->push_back(edit{ "",invertion });
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
	cout << endl;
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

UI::~UI() {

}