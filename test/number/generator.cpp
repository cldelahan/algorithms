#include <iostream>
#include "../../src/simulation/random.h"

namespace Test::Number::Generator
{

    /**
     * @brief Returns a random in the range [low, high) uniformly
     * 
     * @param low The lower bound of the range, inclusive
     * @param high The upper bound of the range, exclusive
     * @return int A random integer
     */
    int generate_int(int low, int high)
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
    float generate_float(float low, float high)
    {
        return Simulation::Random::random_float(low, high);
    }

    namespace
    {
        [[maybe_unused]] float generate_normal(float mean, float std)
        {
            throw std::logic_error("Not yet implemented");
        }
    }

}