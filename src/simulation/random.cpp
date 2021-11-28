#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "random.h"

namespace Simulation::Random
{

    bool ri_seeded = false; // Have we already seeded RNG?

    /**
     * @brief Returns a random in the range [low, high) uniformly
     * 
     * @param low The lower bound of the range, inclusive
     * @param high The upper bound of the range, exclusive
     * @return int A random integer
     */
    int random_int(int low, int high)
    {
        if (!ri_seeded)
        {
            srand((time(NULL)));
            ri_seeded = true;
        }
        return rand() % (high - low) + low;
    }

    /**
     * @brief Returns a random float in range [low, high) uniformly
     * 
     * @param low The lower bound of the range
     * @param high The upper bound of the range
     * @return float A random floating-point variable
     */
    float random_float(float low, float high)
    {
        if (!ri_seeded)
        {
            srand((time(NULL)));
            ri_seeded = true;
        }
        float r = static_cast<float>(rand()) / static_cast<float>((RAND_MAX));
        return r * (high - low) + low;
    }

    /**
     * @brief Returns an array of n pairwise independent bits
     * 
     * @param n A prime number of how many pairwise independent bits to return. 
     * @return std::vector<int> The vector of bits, each stored as an int
     */
    std::vector<int> pairwise_random_bits(int n)
    {
        std::vector<int> output(n, 0);
        // TODO: Should these be n or n + 1
        int a = random_int(1, n + 1);
        int b = random_int(1, n + 1);
        std::cout << "Pairwise: " << a << std::endl;
        std::cout << "Pairwise: " << b << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cout << "Ouput: " << (a * (i + 1) + b) % n << std::endl;
            output[i] = (a * (i + 1) + b) % n;
            output[i] = output[i] % 2;
        }
        return output;
    }

    /**
     * @brief Returns an array of n k-wise independent bits
     * 
     * @param k What k-wise independence (2 is pairwise, 3 is 3-wise, etc.)
     * @param n How many k-wise independent bits to return
     * @return std::vector<int> The vector of bits, each stored as an int
     */
    std::vector<int> kwise_random_bits(int k, int n)
    {
        std::vector<int> output(n, 0);
        // Create vector of coefficients to generate random transformation
        std::vector<int> coef(k, 0);
        for (int i = 0; i < k; i++)
        {
            std::cout << "Random: " << random_int(1, n + 1) << std::endl;
            coef[i] = random_int(1, n + 1);
        }
        for (int i = 0; i < n; i++)
        {
            // Compute polynomial
            int sum = 0;
            for (int j = 0; j < k; j++)
            {
                sum += coef[j] * (int)std::pow(i + 1, j);
            }
            output[i] = sum % n;
            output[i] = output[i] % 2;
        }
        return output;
    }

}