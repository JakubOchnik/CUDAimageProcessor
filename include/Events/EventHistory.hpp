#pragma once
#include <Consts/Errors.hpp>
#include <MainHandler/definitions.hpp>
#include <UI/UIdefinitions.hpp>
#include <stdexcept>
#include <variant>
#include <vector>

struct Event
{
	Event(GenericProgramEvent ev) : content(ev){};
	Event(std::runtime_error ex) : content(ex){};
	std::variant<GenericProgramEvent, std::runtime_error> content;
};

class EventHistory
{
	std::vector<Event> eventQueue;

public:
	[[nodiscard]] std::string getEvents() const;
	void					  clearEvents();
	void					  addEvent(const GenericProgramEvent& e);
	void					  addEvent(const std::runtime_error& e);

	bool isEmpty() const;
};
