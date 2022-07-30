#include <iostream>

#include "../../src/simulation/random.h"
#include "generator.h"

namespace Test::Generator
{

    /**
     * @brief Generates an int from an input (namely
     *      returning itself)
     *
     * @param num The input
     * @return int The generated int
     */
    int generate_self_int(int num)
    {
        return num;
    }

    /**
     * @brief Generates a float from an input (namely
     *      returning itself)
     *
     * @param num The input
     * @return float The generated float
     */
    float generate_self_float(float num)
    {
        return num;
    }

    /**
     * @brief Returns a random in the range [low, high) uniformly
     *
     * @param low The lower bound of the range, inclusive
     * @param high The upper bound of the range, exclusive
     * @return int A random integer
     */
    int generate_uniform_int(int low, int high)
    {
        return Simulation::Random::random_int(low, high);
    }

    /**
     * @brief Returns a random float in range [low, high) uniformly
     *
     * @param low The lower bound of the range
     * @param high The upper bound of the range
     * @return float A random floating-point variable
     */
    float generate_uniform_float(float low, float high)
    {
        return Simulation::Random::random_float(low, high);
    }

    /**
     * @brief Returns a random positive int in range [0, high) uniformly
     *
     * @param high The upper bound of the range
     * @return int A random integer
     */
    int generate_uniform_positive_int(int high)
    {
        return generate_uniform_int(0, high);
    }

    /**
     * @brief Returns a random float in range [0, high) uniformly
     *
     * @param high
     * @return float
     */
    float generate_uniform_positive_float(float high)
    {
        return generate_uniform_float(0., high);
    }

    namespace
    {
        [[maybe_unused]] float generate_normal_float(float mean, float std)
        {
            throw std::logic_error("Not yet implemented");
        }
    }

}