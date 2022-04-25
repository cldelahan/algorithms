#include <iostream>

#include "comparison.h"
#include "../timer/timer.h"
#include "../../src/array/mean.h"
#include "../../src/array/variance.h"

namespace Test::Graph::Comparison
{
    ComparisonResult compare(int (*a1)(int), int (*a2)(int), int input, int iterations)
    {
        std::vector<float> a1_times(iterations);
        std::vector<float> a2_times(iterations);

        for (int i = 0; i < iterations; i++)
        {
            Timer::Timer::start_timer();
            (*a1)(input); // Run second algorithm
            Timer::Timer::end_timer();
            a1_times[i] = Timer::Timer::get_time_in_millis();
        }

        for (int i = 0; i < iterations; i++)
        {
            Timer::Timer::start_timer();
            (*a2)(input); // Run second algorithm
            Timer::Timer::end_timer();
            a2_times[i] = Timer::Timer::get_time_in_millis();
        }

        ComparisonResult result;
        result.number_iterations = iterations;
        result.first_time_millis = Array::Mean::mean_deterministic_linear(a1_times);
        result.first_variance = Array::Variance::variance_deterministic_linear(a1_times);
        result.second_time_millis = Array::Mean::mean_deterministic_linear(a2_times);
        result.second_variance = Array::Variance::variance_deterministic_linear(a2_times);
        return result;
    }
}