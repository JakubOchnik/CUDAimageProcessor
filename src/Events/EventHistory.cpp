#include <Consts/Errors.hpp>
#include <Consts/GenericEvents.hpp>
#include <Events/EventHistory.hpp>
#include <UI/UIdefinitions.hpp>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

std::string EventHistory::getEvents() const
{
	std::string out;
	for (const auto& event : eventQueue)
	{
		if (event.content.index() == 0)
		{
			// Holds GenericProgramEvent
			event::GenericProgramEvent ev{
				std::get<event::GenericProgramEvent>(event.content)};
			out += consts::ui::EVENT_TEXT_PROMPTS.at(ev);
		}
		else
		{
			// Holds exception
			std::runtime_error ex{std::get<std::runtime_error>(event.content)};
			out += ex.what();
		}
		out += "\n";
	}
	return out;
}

void EventHistory::clearEvents()
{
	eventQueue.clear();
}

void EventHistory::addEvent(const event::GenericProgramEvent& e)
{
	eventQueue.emplace_back(e);
}

void EventHistory::addEvent(const std::runtime_error& e)
{
	eventQueue.emplace_back(e);
}

bool EventHistory::isEmpty() const
{
	return eventQueue.empty();
}
