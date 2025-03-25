#pragma once
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

// Not yet used event system
template <typename ReturnType, typename... Param>
class Event
{
public:
    Event() = default;

    void AddListener(std::function<ReturnType(Param...)> function)
    {
        listeners.push_back(function);
    }

    void RemoveListener(std::function<ReturnType(Param...)> function)
    {
        auto it = std::remove_if(listeners.begin(), listeners.end(),
            [&function](const auto& listener) {
                return listener.target_type() == function.target_type() &&
                    listener.target<void>() == function.target<void>();
            });
        listeners.erase(it, listeners.end());
    }

    void Invoke(Param... parameters)
    {
        for (const auto& listener : listeners)
        {
            listener(parameters...);
        }
    }

private:
    std::vector<std::function<ReturnType(Param...)>> listeners;
};
