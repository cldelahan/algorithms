#ifndef ALGO_TEST_TIMER
#define ALGO_TEST_TIMER

#include <time.h>

namespace Timer::Timer
{
    void start_timer();
    void end_timer();
    float get_time_in_millis();
}

#endif