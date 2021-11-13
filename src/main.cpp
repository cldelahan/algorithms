#include <iostream>
#include <set>
#include <utility>

#include "stdio.h"
#include "array/mean.h"
#include "graph/vertex_cover.h"
#include "graph/minimum_spanning_tree.h"
#include "array/sampling.h"
#include "simulation/random.h"
#include "utils/print.h"
#include "number/prime_test.h"
#include "number/fibonacci.h"
#include "../test/timer/timer.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello, world" << std::endl;

    std::vector<float> vec;
    vec.push_back(10.);
    vec.push_back(60.);
    vec.push_back(100.);
    float result = Array::Mean::mean_deterministic_linear(vec);
    std::cout << "Result, " << result << std::endl;

    float sampled = Array::Sampling::sampling_randomized_reservoir(vec);
    std::cout << "Sampled Value: " << sampled << std::endl;

    std::vector<std::pair<int, int>> edges;
    edges.push_back(std::pair<int, int>(1, 5));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(3, 4));
    edges.push_back(std::pair<int, int>(4, 5));

    std::cout << "Vertex Cover 2-approx" << std::endl;
    std::set<int> vertex_cover = Graph::VertexCover::vertex_cover_approx(edges);
    for (int s : vertex_cover)
    {
        std::cout << "Vertex: " << s << std::endl;
    }

    std::vector<std::vector<int>> graph{{0, 5, 2, 3, 2},
                                        {5, 0, 2, 1, 0},
                                        {2, 2, 0, 4, 2},
                                        {3, 1, 4, 0, 4},
                                        {2, 0, 2, 4, 0}};
    std::vector<std::vector<int>> mst = Graph::MinimumSpanningTree::mst_deterministic_prims(graph);
    std::cout << "MST" << std::endl;
    Utils::Print::print_matrix(mst);

    std::cout << "11 pairwise independent bits" << std::endl;
    std::vector<int> p_bits = Simulation::Random::pairwise_random_bits(10);
    Utils::Print::print_vector(p_bits);

    std::cout << "11 5-wise independent bits" << std::endl;
    std::vector<int> bits = Simulation::Random::kwise_random_bits(5, 11);
    Utils::Print::print_vector(bits);

    std::cout << "200 prime test" << std::endl;
    std::cout << Number::PrimeTest::prime_test_naive(200) << std::endl;
    std::cout << "59 primetest" << std::endl;
    std::cout << Number::PrimeTest::prime_test_naive(59) << std::endl;

    std::cout << "Fib 2: " << Number::Fibonacci::fibonacci_closed_form(2) << std::endl;
    std::cout << "Fib 5: " << Number::Fibonacci::fibonacci_closed_form(5) << std::endl;
    std::cout << "Fib 2: " << Number::Fibonacci::fibonacci_dynamic_programming(2) << std::endl;
    std::cout << "Fib 5: " << Number::Fibonacci::fibonacci_dynamic_programming(5) << std::endl;

    Timer::Timer::start_timer();
    Timer::Timer::end_timer();
    std::cout << "Result: " << Timer::Timer::get_time_in_millis() << std::endl;
}