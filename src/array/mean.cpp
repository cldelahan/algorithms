#include <iostream>
#include <vector>

#include "mean.h"

namespace Array::Mean
{

    /**
     * @brief Computing the mean of an array in linear time
     * 
     * @param vec An vector of floats
     * @return float The mean
     */
    float mean_deterministic_linear(std::vector<float> vec)
    {
        float sum = 0.;
        for (float v : vec)
        {
            sum += v;
        }
        return sum / vec.size();
    }
}
