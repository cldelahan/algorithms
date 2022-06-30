#ifndef ALGO_SRC_SIMULATION_RANDOM
#define ALGO_SRC_SIMULATION_RANDOM

#include <vector>

namespace Simulation::Random
{
    int random_int(int, int);
    float random_float(float, float);
    std::vector<int> pairwise_random_bits(int);
    std::vector<int> kwise_random_bits(int, int);
    std::vector<int> random_unique_ints_fisheryates(int, int, int);
    std::vector<int> random_unique_ints_sort(int, int, int);
}

#endif