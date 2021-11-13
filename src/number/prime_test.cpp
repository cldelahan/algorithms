#include <iostream>
#include <math.h>

#include "prime_test.h"

namespace Number::PrimeTest
{
    /**
     * @brief Determines whether a positive integer n is prime. Iterates through 
     *      all numbers of form 6k +- 1 until sqrt(n) and checks if n is divisible.
     * 
     * @param n Positve integer 
     * @return bool Whether n is prime
     */
    bool prime_test_naive(int n)
    {
        if (n <= 3)
        {
            return n > 1;
        }

        if (n % 2 == 0 || n % 3 == 0)
        {
            return false;
        }

        int k = 5;
        while (pow(k, 2) <= n)
        {
            if (n % k == 0 || n % (k + 1) == 0)
            {
                return false;
            }
            k += 6;
        }
        return true;
    }

}