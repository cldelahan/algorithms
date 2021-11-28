#include <iostream>
#include <set>
#include <utility>

#include "stdio.h"
#include "array/mean.h"
#include "graph/vertex_cover.h"
#include "graph/minimum_spanning_tree.h"
#include "graph/steiner_tree.h"
#include "array/sampling.h"
#include "simulation/random.h"
#include "utils/print.h"
#include "number/prime_test.h"
#include "number/fibonacci.h"
#include "../test/timer/timer.h"
#include "../test/number/comparison.h"

int main(int argc, char *argv[])
{

    /*
        This file contains sample / test functionality for the package. Please
        uncomment to test functionality
    */

    /*
        Array operations
    */

    /* 
    std::vector<float> vec;
    vec.push_back(10.);
    vec.push_back(60.);
    vec.push_back(100.);
    float result = Array::Mean::mean_deterministic_linear(vec);
    std::cout << "Result, " << result << std::endl;

    float sampled = Array::Sampling::sampling_randomized_reservoir(vec);
    std::cout << "Sampled Value: " << sampled << std::endl;
    */

    /*
        Graph operations
    */

    using namespace Graph;

    // Using constructor operator

    CostMatUndirGraph test({{NO_EDGE, 5, 2, 3, 2},
                            {5, NO_EDGE, 2, 1, NO_EDGE},
                            {2, 2, NO_EDGE, 4, 2},
                            {3, 1, 4, NO_EDGE, 4},
                            {2, NO_EDGE, 2, 4, NO_EDGE}});

    Utils::Print::print_matrix(test.graph, NO_EDGE, ",");

    // Vertex Cover

    EdgeListUndirGraph vc_graph;
    vc_graph.graph.push_back(Edge(1, 5));
    vc_graph.graph.push_back(Edge(1, 2));
    vc_graph.graph.push_back(Edge(2, 3));
    vc_graph.graph.push_back(Edge(3, 4));
    vc_graph.graph.push_back(Edge(4, 5));

    vc_graph.graph.push_back(Edge(5, 1));
    vc_graph.graph.push_back(Edge(2, 1));
    vc_graph.graph.push_back(Edge(3, 2));
    vc_graph.graph.push_back(Edge(4, 3));
    vc_graph.graph.push_back(Edge(5, 4));

    std::cout << "Vertex Cover 2-approx" << std::endl;
    std::set<int> vertex_cover = Graph::VertexCover::vertex_cover_approx(vc_graph);
    for (int s : vertex_cover)
    {
        std::cout << "Vertex: " << s << std::endl;
    }

    // Minimum Spanning Tree

    CostMatUndirGraph mst_graph;
    mst_graph.graph = CostMatGraph{{NO_EDGE, 5, 2, 3, 2},
                                   {5, NO_EDGE, 2, 1, NO_EDGE},
                                   {2, 2, NO_EDGE, 4, 2},
                                   {3, 1, 4, NO_EDGE, 4},
                                   {2, NO_EDGE, 2, 4, NO_EDGE}};
    CostMatUndirGraph mst = MinimumSpanningTree::mst_deterministic_prims(mst_graph);
    std::cout << "MST" << std::endl;
    Utils::Print::print_matrix(mst.graph, NO_EDGE, ",");

    // Steiner Tree

    CostMatUndirGraph stm_graph;
    stm_graph.graph = CostMatGraph{{NO_EDGE, 5, 3, 6, 1, 3, 4},
                                   {5, NO_EDGE, 3, 6, 1, 3, 4},
                                   {3, 3, NO_EDGE, 6, 1, 3, 4},
                                   {6, 6, 6, NO_EDGE, 1, 3, 4},
                                   {1, 1, 1, 1, NO_EDGE, 3, 4},
                                   {3, 3, 3, 3, 3, NO_EDGE, 4},
                                   {4, 4, 4, 4, 4, 4, NO_EDGE}};
    Verticies terminals = Verticies{1, 3, 4, 5};

    CostMatUndirGraph steinertree = SteinerTree::steinertreemetric_approx_prims(stm_graph, terminals);
    std::cout << "Steiner tree" << std::endl;
    std::cout << "Is example a metric? (1 - yes, 0 - no): " << Graph::is_metric(stm_graph) << std::endl;
    std::cout << "Cost of connection: " << Graph::edge_cost(steinertree) << std::endl;
    Utils::Print::print_matrix(steinertree.graph, NO_EDGE, ",");

    /*
        Simulation operations
    */

    std::cout << "11 pairwise independent bits" << std::endl;
    std::vector<int> p_bits = Simulation::Random::pairwise_random_bits(11);
    Utils::Print::print_vector(p_bits);

    std::cout << "11 5-wise independent bits" << std::endl;
    std::vector<int> bits = Simulation::Random::kwise_random_bits(5, 11);
    Utils::Print::print_vector(bits);

    /*
        Number operations
    */

    /*
    std::cout << "200 prime test" << std::endl;
    std::cout << Number::PrimeTest::prime_test_naive(200) << std::endl;
    std::cout << "59 primetest" << std::endl;
    std::cout << Number::PrimeTest::prime_test_naive(59) << std::endl;

    std::cout << "Fib 2: " << Number::Fibonacci::fibonacci_closed_form(2) << std::endl;
    std::cout << "Fib 5: " << Number::Fibonacci::fibonacci_closed_form(5) << std::endl;
    std::cout << "Fib 2: " << Number::Fibonacci::fibonacci_dynamic_programming(2) << std::endl;
    std::cout << "Fib 5: " << Number::Fibonacci::fibonacci_dynamic_programming(5) << std::endl;
    */

    /*
        Timer operations
    */

    /*
    Timer::Timer::start_timer();
    Timer::Timer::end_timer();
    std::cout << "Result: " << Timer::Timer::get_time_in_millis() << std::endl;
    */

    /* 
        Comparison operations
    */

    /*
    int test_number = 100000;
    Test::Number::Comparison::ComparisonResult result =
        Test::Number::Comparison::compare(
            Number::Fibonacci::fibonacci_dynamic_programming,
            Number::Fibonacci::fibonacci_closed_form, test_number);

    std::cout << "Fibonocci Dynamic Programming" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result.first_time_millis << std::endl;
    std::cout << "Variance (ms): " << result.first_variance << std::endl;

    std::cout << "Fibonocci Closed Form" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result.second_time_millis << std::endl;
    std::cout << "Variance (ms): " << result.second_variance << std::endl;
    */
}