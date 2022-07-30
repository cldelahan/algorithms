#ifndef ALGO_TEST_NUMBER_GEN
#define ALGO_TEST_NUMBER_GEN

namespace Test::Generator
{
    int generate_self_int(int);
    float generate_self_float(float);
    int generate_uniform_int(int, int);
    float generate_uniform_float(float, float);
    int generate_uniform_positive_int(int);
    float generate_uniform_positive_float(float);
    float generate_normal_float(float, float);
}

#endif