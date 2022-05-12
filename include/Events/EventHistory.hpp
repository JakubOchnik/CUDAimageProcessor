#pragma once

#include <Consts/GenericEvents.hpp>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

struct Event
{
	Event(event::GenericProgramEvent ev) : content(ev){};
	Event(std::runtime_error ex) : content(ex){};
	std::variant<event::GenericProgramEvent, std::runtime_error> content;
};

class EventHistory
{
	std::vector<Event> eventQueue;

public:
	[[nodiscard]] std::string getEvents() const;
	void					  clearEvents();
	void					  addEvent(const event::GenericProgramEvent& e);
	void					  addEvent(const std::runtime_error& e);

	bool isEmpty() const;
};
