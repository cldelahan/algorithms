#include <iostream>
#include <math.h>

namespace Number::Fibonacci
{

    /**
     * @brief Returns the nth Fibonacci number for positive integer n, using
     *      Binet's closed form for the nth Fibonacci number
     * 
     * @param n A positive integer
     * @return int The value of the nth fibonacci
     */
    int fibonacci_closed_form(int n)
    {
        double sqrt5 = sqrt(5);
        double Phi = (1 + sqrt5) / 2.;
        double phi = (1 - sqrt5) / 2.;
        int result = (int)round((pow(Phi, n) - pow(phi, n)) / sqrt5);

        return result;
    }

    /**
     * @brief Returns the nth Fibonacci number for positive interger n, using
     *      dynamic programming for iterating to the nth Fibonacci number
     * 
     * @param n A positive integer
     * @return int The value of the nth fibonacci
     */
    int fibonacci_dynamic_programming(int n)
    {
        if (n <= 0)
        {
            return 0;
        }
        if (n <= 2)
        {
            return 1;
        }
        int l1 = 1, l2 = 1;
        int sum = 2;
        for (int i = 3; i <= n; i++)
        {
            sum = l1 + l2;
            l2 = l1;
            l1 = sum;
        }
        return sum;
    }

}