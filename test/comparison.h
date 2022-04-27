/**
 * @file comparison.h
 * @author Conner Delahanty (cldelahan@gmail.com)
 * @brief Allows two algorithms to be compared for runtime
 *      analysis (faster run and variances), on a specific
 *      input.
 *      NOTE: The functions are defined in this header file because
 *      using templates required either moving the implementation code
 *      to the header or explicitally instanciating the templates in the cpp
 *      (and I chose the former).
 *      As a result, the functions must also be denoted `inline` since
 *      the linker would complain about multiple definitions if two
 *      separate files import the print.h
 *      NOTE: Also, as I understand, there is no good way to pass multiple
 *      arguments to these functions (the potentially multiple input
 *      arguments to an algorithm). As such, there are multiple
 *      functions for each possible number of arguments
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ALGO_TEST_COMPARISON
#define ALGO_TEST_COMPARISON

#include <vector>
#include "timer/timer.h"

namespace Test::Comparison
{
    class ComparisonResult
    {
    public:
        // TODO: Add additional variables to comparision result
        // TODO: Add tracking for which name was which
        // TODO: Elevate to common area
        int number_iterations;
        float first_time_millis;
        float first_variance;
        float second_time_millis;
        float second_variance;
    };

    ComparisonResult compute_comparison_result(std::vector<float> *a1_times, std::vector<float> *a2_times);

    /**
     * @brief Compares two algorithms that accept the same input,
     *      and returns a class containing runtime performance
     *      data. The input must be one argument.
     *      NOTE: The intent is that the types U and V (the output
     *      for algorithm one and two) are the same. However,
     *      since some algorithms best are structured to return
     *      different types, it has been decided to  not enforce
     *      that their return types are the same
     *
     * @tparam T The input type of the algorithm
     * @tparam U The output type of algorithm one
     * @tparam V The output type of algorithm two
     * @param a1 Algorithm one function pointer
     * @param a2 Algorithm two function pointer
     * @param input The input to test both algorithms with
     * @param iterations Number of iterations to assess
     * @return ComparisonResult The result of the comparision
     */
    template <typename T, typename U, typename V>
    inline ComparisonResult compare(U (*a1)(T), V (*a2)(T), T input, int iterations = 1000)
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

        ComparisonResult result = compute_comparison_result(&a1_times, &a2_times);
        return result;
    }

    /**
     * @brief Compares two algorithms that accept the same input,
     *      and returns a class containing runtime performance
     *      data. The input must be two arguments.
     *      NOTE: The intent is that the types U and V (the output
     *      for algorithm one and two) are the same. However,
     *      since some algorithms best are structured to return
     *      different types, it has been decided to  not enforce
     *      that their return types are the same
     *
     * @tparam T1 The first input type of the algorithm
     * @tparam T2 The second input type of the algorithm
     * @tparam U The output type of algorithm one
     * @tparam V The output type of algorithm two
     * @param a1 Algorithm one function pointer
     * @param a2 Algorithm two function pointer
     * @param input The input to test both algorithms with
     * @param iterations Number of iterations to assess
     * @return ComparisonResult The result of the comparision
     */
    template <typename T1, typename T2, typename U, typename V>
    inline ComparisonResult compare(U (*a1)(T1, T2), V (*a2)(T1, T2), T1 input1, T2 input2, int iterations = 1000)
    {
        std::vector<float> a1_times(iterations);
        std::vector<float> a2_times(iterations);

        for (int i = 0; i < iterations; i++)
        {
            Timer::Timer::start_timer();
            (*a1)(input1, input2); // Run second algorithm
            Timer::Timer::end_timer();
            a1_times[i] = Timer::Timer::get_time_in_millis();
        }

        for (int i = 0; i < iterations; i++)
        {
            Timer::Timer::start_timer();
            (*a2)(input1, input2); // Run second algorithm
            Timer::Timer::end_timer();
            a2_times[i] = Timer::Timer::get_time_in_millis();
        }

        ComparisonResult result = compute_comparison_result(&a1_times, &a2_times);
        return result;
    }
}

#endif