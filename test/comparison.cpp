/**
 * @file comparison.cpp
 * @author Conner Delahanty (cldelahan@gmail.com)
 * @brief Implementation of some comparison functionality
 * @version 0.1
 * @date 2022-04-24
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "comparison.h"
#include "../src/array/mean.h"
#include "../src/array/variance.h"

namespace Test::Comparison
{
    ComparisonResult compute_comparison_result(std::vector<float> *a1_times, std::vector<float> *a2_times)
    {
        ComparisonResult result;
        result.number_iterations = (*a1_times).size();
        result.first_time_millis = Array::Mean::mean_deterministic_linear(*a1_times);
        result.first_variance = Array::Variance::variance_deterministic_linear(*a1_times);
        result.second_time_millis = Array::Mean::mean_deterministic_linear(*a2_times);
        result.second_variance = Array::Variance::variance_deterministic_linear(*a2_times);
        return result;
    }
}