#pragma once

#include <chrono>
#include <functional>
#include <thread>

// Simple scheduled function that creates a thread
// Sleeps for a delay and then calls the function

class ScheduledFunction {
    std::thread               t;
    std::chrono::milliseconds delay;
    std::function<void()>     target;
    bool                      running;

public:
    ScheduledFunction(std::function<void()> &&f) : target(std::move(f)) {
    }

    // Blocks until thread stops
    ~ScheduledFunction() {
        Stop();
    }

    void Delay(std::chrono::milliseconds d) {
        delay = d;
    }

    void Start() {
        running = true;
        t       = std::thread{
            [this]() {
                while (running) {
                    std::this_thread::sleep_for(delay);
                    target();
                }
            }};
    }

    // Blocks until thread stops
    void Stop() {
        running = false;

        if (t.joinable()) t.join();
    }
};