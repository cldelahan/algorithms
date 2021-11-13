#include <iostream>
#include <vector>
#include "math.h"

#include "variance.h"
#include "mean.h"

namespace Array::Variance
{

    /**
     * @brief Computing the variance of an array in linear time
     * 
     * @param vec An vector of floats
     * @return float The variance
     */
    float variance_deterministic_linear(std::vector<float> vec)
    {
        float mean = Array::Mean::mean_deterministic_linear(vec);
        float var = 0.0;
        for (float v : vec)
        {
            var += pow(v - mean, 2.);
        }

        return var / vec.size();
    }
}
