#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <algorithm>

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

    /**
     * @brief Genereates random unique ints using the Fisher Yates algorithm,
     *      with a slight modification of eraseing the random element in the
     *      array for simple implementation (with no affect on performance).
     *      Generates n numbers from low to high, without repetition.
     *      Returns empty array if it is not possible, or if high <= low.
     *      This algorithm is technically O(n^2)
     *
     *
     * @cite https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
     *
     * @param n The number of ints to generate
     * @param low The low range of the ints
     * @param high The high range of the ints
     * @return std::vector<int> The unique ints from [low, high)
     */
    std::vector<int> random_unique_ints_fisheryates(int n, int low, int high)
    {
        if (n > high - low || high <= low)
        {
            return {};
        }
        std::vector<int> output;
        // Create and populate arr with values
        // from low to high
        std::vector<int> arr(high - low);
        for (int i = low; i < high; i++)
        {
            arr[i - low] = i;
        }

        int max_index = high - low;
        for (int i = 0; i < n; i++)
        {
            int index = random_int(0, max_index - i);
            output.push_back(arr[index]);
            arr.erase(arr.begin() + index);
        }
        return output;
    }

    /**
     * @brief Generate random unique integers using a shuffling method,
     *      where an array of the ranged ints is shuffled, and then
     *      the first n is removed. Shuffling happens in O(n) time,
     *      and thus the entire algorithm is O(n)
     *
     * @param n The number of ints to generate
     * @param low The low range of the ints
     * @param high The high range of the ints
     * @return std::vector<int> The unique ints from [low, high)
     */
    std::vector<int> random_unique_ints_sort(int n, int low, int high)
    {

        if (!ri_seeded)
        {
            srand((time(NULL)));
            ri_seeded = true;
        }

        if (n > high - low || high <= low)
        {
            return {};
        }
        std::vector<int> output(n);
        // Create and populate arr with values
        // from low to high
        std::vector<int> arr(high - low);
        for (int i = low; i < high; i++)
        {
            arr[i - low] = i;
        }

        std::random_shuffle(arr.begin(), arr.end());

        for (int i = 0; i < n; i++)
        {
            output[i] = arr[i];
        }

        return output;
    }

}