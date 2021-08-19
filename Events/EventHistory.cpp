#include "EventHistory.hpp"

std::string [[nodiscard]] EventHistory::getEvents() const
{
	std::string out;
	for (const auto& event : eventQueue)
	{
		out += EVENT_TEXT_PROMPTS.at(event);
		out += "\n";
	}
	return out;
}

void EventHistory::clearEvents()
{
	eventQueue.clear();
}

void EventHistory::addEvent(const Event& e)
{
	eventQueue.push_back(e);
}

bool EventHistory::isEmpty() const
{
	return eventQueue.empty();
}
