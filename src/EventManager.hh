
#pragma once

#include <vector>
#include <functional>

class EventManager
{
private:
    std::vector<std::function<void()>> events;

public:
    void addEvent(std::function<void()> event);
    void notifyEvents();
};
