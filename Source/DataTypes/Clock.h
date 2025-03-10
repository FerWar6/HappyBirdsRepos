#pragma once
#include <chrono>

class Clock {
public:
    Clock() {
        startTime = std::chrono::high_resolution_clock::now(); 
    }

    void Reset() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    double GetTimeInSeconds() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

    double GetTimeInMicroSeconds() {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed = now - startTime;
        return elapsed.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
};
