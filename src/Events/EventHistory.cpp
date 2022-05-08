#include <Events/EventHistory.hpp>

std::string EventHistory::getEvents() const
{
	std::string out;
	for (const auto& event : eventQueue)
	{
		if (event.content.index() == 0)
		{
			// Holds GenericProgramEvent
			GenericProgramEvent ev{std::get<GenericProgramEvent>(event.content)};
			out += EVENT_TEXT_PROMPTS.at(ev);
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

void EventHistory::addEvent(const GenericProgramEvent& e)
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
