#include <chrono>
#include <iostream>

#include "timer.h"

namespace Timer::Timer
{
    bool timer_running = false;
    std::chrono::_V2::system_clock::time_point s_time;
    std::chrono::_V2::system_clock::time_point e_time;

    void start_timer()
    {
        if (timer_running)
        {
            std::cout << "WARNING: Timer already started. Start_time overwritten." << std::endl;
        }
        timer_running = true;
        s_time = std::chrono::high_resolution_clock::now();
    }

    void end_timer()
    {
        if (!timer_running)
        {
            std::cout << "WARNING: Timer already stopped. End_time overwritten." << std::endl;
        }
        timer_running = false;
        e_time = std::chrono::high_resolution_clock::now();
    }

    float get_time_in_millis()
    {
        if (timer_running)
        {
            std::cout << "WARNING: Timer is presently running. End_time overwritten." << std::endl;
            end_timer();
        }
        return std::chrono::duration<float, std::milli>(e_time - s_time).count();
    }
}