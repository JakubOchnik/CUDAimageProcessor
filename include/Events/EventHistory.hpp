#pragma once
#include <vector>
#include <MainHandler/definitions.hpp>
#include <UI/UIdefinitions.hpp>
#include <Consts/Errors.hpp>
#include <stdexcept>
#include <variant>

struct Event
{
	Event(GenericEvent ev) : content(ev) {};
	Event(std::runtime_error ex) : content(ex) {};
	std::variant<GenericEvent, std::runtime_error> content;
};

class EventHistory
{
	std::vector<Event> eventQueue;
public:
	[[nodiscard]] std::string getEvents() const;
	void clearEvents();
	void addEvent(const GenericEvent& e);
	void addEvent(const std::runtime_error& e);

	bool isEmpty() const;
};
