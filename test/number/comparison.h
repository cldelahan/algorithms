#ifndef ALGO_TEST_NUMBER_COMPARISON
#define ALGO_TEST_NUMBER_COMPARISON

namespace Test::Number::Comparison
{
    class ComparisonResult
    {
    public:
        // TODO: Add additional variables to comparision result
        // TODO: Add tracking for which name was which
        // TODO: Elevate to common area
        int number_iterations;
        float first_time_millis;
        float first_variance;
        float second_time_millis;
        float second_variance;
    };

    ComparisonResult compare(int (*a1)(int), int (*a2)(int), int input, int iterations = 1000);

}

#endif