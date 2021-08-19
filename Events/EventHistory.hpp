#pragma once
#include <vector>
#include "../MainHandler/definitions.h"
#include "../UI/UIdefinitions.h"
class EventHistory
{
	std::vector<Event> eventQueue;
public:
	[[nodiscard]] std::string getEvents() const;
	void clearEvents();
	void addEvent(const Event& e);

	bool isEmpty() const;
};
