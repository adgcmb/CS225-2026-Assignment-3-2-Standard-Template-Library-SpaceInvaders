#include "EventManager.hh"

void EventManager::addEvent(std::function<void()> event)
{
    events.push_back(event);
}

void EventManager::notifyEvents()
{
    for (auto& event : events)
    {
        event();
    }

    events.clear();
}
