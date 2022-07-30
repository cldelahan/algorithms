/**
 * @file runtime.h
 * @author Conner Delahanty (cldelahan@gmail.com)
 * @brief Attempts to solve for the runtime of an algorithm, given that
 *      algorithm and a generator function, where each input to the generator
 *      function is a imput to the runtime equation.
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
 * @date 2022-07-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ALGO_TEST_RUNTIME
#define ALGO_TEST_RUNTIME

#include <vector>

namespace Test::Runtime
{
    // Input sizes to test on a passed algorithm
    static std::vector<int> INPUT_SIZES_TO_EVALUATE = {
        1,
        2,
        4,
        8,
        16,
        32,
        64,
        128,
        256,
        512,
        1028,
        2048,
        4096,
        8192,
        16384,
        32768};

    class RuntimeResult
    {
    public:
        // Simple analysis assuming polynomial in up-to
        // 2 inputs. Eventual logic should be added for
        // exponential, non-polynomial, and logarithmic

        // The i,j-th coordinate of an n-dim matrix represents the coefficient
        // of x^(n-i)*y^(n-j) in a runtime best-fit.
        // i.e. in a 2x2, let  a = coeffs[0][0], b = coeffs[0][1],
        // c = coeffs[1][0], and d = coeffs[1][1], then the best fit was
        // a + bx + cy + dxy
        std::vector<std::vector<float>> coeffs;
        // The i,j-th is a boolean if it is determined that that coeffecient
        // is part of the fit
        std::vector<std::vector<bool>> big_oh;
    };

    /**
     * @brief Takes an algorithm and a generator that returns inputs
     *      to that algorithm and returns a class containing an evaluated
     *      runtime performance for that algorithm.
     *
     *
     * @tparam U The output of the algorithm (not used)
     * @tparam T The input type of the algorithm
     * @tparam I The input type of the generator (to vary size)
     * @param a Algorithm function pointer
     * @param cutoff_runtime The largest time that runtime stops
     * @param iterations Number of iterations to assess
     * @return RuntimeResult The result of computing the runtime
     */
    template <typename U, typename T, typename I>
    inline RuntimeResult compute_runtime(U (*a)(T), T (*g)(I), float cutoff_runtime = 0.5, int iterations = 20)
    {
        std::vector<float> time_per_sizes;
        for (int input : INPUT_SIZES_TO_EVALUATE)
        {
            std::vector<float> times(iterations);
            for (int i = 0; i < iterations; i++)
            {
                Timer::Timer::start_timer();
                T alg_input = (*g)(input); // Get input to algorithm
                (*a)(alg_input);           // Run algorithm
                Timer::Timer::end_timer();
                times[i] = Timer::Timer::get_time_in_millis();
            }
            float average_time = Array::Mean::mean_deterministic_linear(times);
            time_per_sizes.push_back(average_time);
            if (average_time > cutoff_runtime)
            {
                break;
            }
        }
        RuntimeResult r;
        r.coeffs = {time_per_sizes};
        return r;
    }
}

#endif