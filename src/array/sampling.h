#ifndef ALGO_SRC_ARRAY_SAMPLING
#define ALGO_SRC_ARRAY_SAMPLING

#include <vector>

namespace Array::Sampling
{
    float sampling_randomized_general(std::vector<float>);
    float sampling_randomized_reservoir(std::vector<float>);
}

#endif