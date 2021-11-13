#include <iostream>
#include <vector>

#include "sampling.h"
#include "../simulation/random.h"

namespace Array::Sampling
{

    /**
     * @brief Samples a vector using a random index 
     * 
     * @param vec The vector to sample from
     * @return float The sampled entry
     */
    float sampling_randomized_general(std::vector<float> vec)
    {
        int index = Simulation::Random::random_int(0, vec.size());
        return vec[index];
    }

    /**
     * @brief Performs reservoir sampling on a vector of floats. Namely, 
     *      returns an element from vec with a probability porportional to
     *      to the number of times that element appears. Runs in an on-line
     *      fashion, and can imagine vec as a stream.
     * 
     * @param vec A vector of floats to sample from
     * @return float The sampled entry
     */
    float sampling_randomized_reservoir(std::vector<float> vec)
    {
        float result = 0.;
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (Simulation::Random::random_int(0, i + 1) == 0)
            {
                result = vec[i];
            }
        }
        return result;
    }
}
