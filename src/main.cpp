#include <iostream>
#include <set>
#include <map>
#include <utility>
#include <algorithm>

#include "stdio.h"
#include "array/mean.h"
#include "array/sampling.h"
#include "graph/minimum_spanning_tree.h"
#include "graph/shortest_path.h"
#include "graph/steiner_tree.h"
#include "graph/vertex_cover.h"
#include "simulation/random.h"
#include "set/set.h"
#include "number/prime_test.h"
#include "number/fibonacci.h"
#include "utils/print.h"
#include "../test/timer/timer.h"
#include "../test/comparison.h"

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

    Utils::Print::print_title("Example Constructor and Print");

    CostMatUndirGraph test({{NO_EDGE, 5, NO_EDGE, NO_EDGE, NO_EDGE},
                            {5, NO_EDGE, 2, NO_EDGE, NO_EDGE},
                            {2, 2, NO_EDGE, 4, 2},
                            {3, 1, 4, NO_EDGE, 4},
                            {2, NO_EDGE, 2, 4, NO_EDGE}});

    Utils::Print::print_matrix<int>(test.graph, NO_EDGE, ",");

    // Dijkstras

    Verticies path = Verticies();
    int length = ShortestPath::shortestpath_deterministic_dijkstras(test, 0, 3, path);
    Utils::Print::print_title("Dijkstras");
    std::cout << "Dijkstra's Run" << std::endl;
    std::cout << "Length: " << length << std::endl;
    Utils::Print::print_vector<Vertex>(path, " ");

    // Floyd-Warshall's

    CostMatGraph shortest_path_tree = CostMatGraph();
    CostMatGraph shortest_paths = ShortestPath::shortestpath_deterministic_floydwarshall(test, shortest_path_tree);
    Utils::Print::print_title("Floyd-Warshall's");
    Utils::Print::print_matrix(shortest_paths, NO_EDGE, ",");
    Verticies shortest_path = ShortestPath::shortestpath_treereconstruct(shortest_path_tree, 0, 3);
    Utils::Print::print_vector<Vertex>(shortest_path, " ");

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

    Utils::Print::print_title("Vertex Cover 2-approx");
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
    Utils::Print::print_title("Minimum Spanning Tree (Prims)");
    CostMatUndirGraph mst = MinimumSpanningTree::mst_deterministic_prims(mst_graph);
    Utils::Print::print_matrix<Vertex>(mst.graph, NO_EDGE, ",");

    // Metric Steiner Tree

    CostMatUndirGraph stm_graph;
    stm_graph.graph = CostMatGraph{{NO_EDGE, 5, 3, 6, 1, 3, 4},
                                   {5, NO_EDGE, 3, 6, 1, 3, 4},
                                   {3, 3, NO_EDGE, 6, 1, 3, 4},
                                   {6, 6, 6, NO_EDGE, 1, 3, 4},
                                   {1, 1, 1, 1, NO_EDGE, 3, 4},
                                   {3, 3, 3, 3, 3, NO_EDGE, 4},
                                   {4, 4, 4, 4, 4, 4, NO_EDGE}};
    Verticies terminals = Verticies{1, 3, 4, 5};

    Utils::Print::print_title("Metric Steiner Tree");
    CostMatUndirGraph steinertree = SteinerTree::steinertreemetric_approx_prims(stm_graph, terminals);
    std::cout << "steinertreemetric_approx_prims()" << std::endl;
    std::cout << "Is example a metric? (1 - yes, 0 - no): " << Graph::is_metric(stm_graph) << std::endl;
    std::cout << "Cost of connection: " << Graph::edge_cost(steinertree) << std::endl;
    Utils::Print::print_matrix<Vertex>(steinertree.graph, NO_EDGE, ",");

    int cost = SteinerTree::steinertreemetric_deterministic_dreyfus(stm_graph, terminals);
    std::cout << "steinertreemetric_deterministic_dreyfus()" << std::endl;
    std::cout << "Is example a metrix? (1 - yes, 0 - no): " << Graph::is_metric(stm_graph) << std::endl;
    std::cout << "Cost of connection: " << cost << std::endl;

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
        Set operations
    */

    Utils::Print::print_title("Set Operations");

    std::set<int> test_set = std::set<int>();
    for (int i = 0; i < 5; i++)
    {
        test_set.insert(i);
    }
    auto list_of_sets = Set::get_subsets_of_size_n(test_set, 3);
    for (std::set<int> s : list_of_sets)
    {
        Utils::Print::print_set(s, "", " ");
    }
    std::cout << std::endl;

    // Test for set of size 0 works

    auto all_subsets = Set::get_all_subsets(test_set, {2, 3});
    for (std::set<int> s : all_subsets)
    {
        Utils::Print::print_set(s, "", " ");
    }

    /*
        Set Difference Testing
    */
    Utils::Print::print_title("Set Difference Testing");
    std::set<int> left_set = std::set<int>();
    std::set<int> right_set = std::set<int>();
    for (int i = 0; i < 5; i++)
    {
        left_set.insert(i);
    }
    right_set.insert(2);
    right_set.insert(1);

    std::set<Vertex> left_minus_right;
    std::set_difference(left_set.begin(), left_set.end(), right_set.begin(), right_set.end(),
                        std::inserter(left_minus_right, left_minus_right.begin()));

    Utils::Print::print_set(left_minus_right, "", " ");
    std::cout << std::endl;

    /*
        Sets as Indices to Maps
    */
    Utils::Print::print_title("Sets as Indicies to Maps");
    std::map<std::set<int>, int> set_map;
    std::set<int> set_a = {1, 2, 3};
    std::set<int> set_b = {2, 3, 4};
    std::set<int> set_c = {4, 5, 6};
    std::set<int> set_d = {3, 2, 1};
    std::set<int> set_e = {1, 2, 3};

    set_map[set_a] = 1;
    set_map[set_b] = 2;
    set_map[set_c] = 3;

    std::cout << "Evaluating set_map at set C" << std::endl;
    std::cout << "Expected: " << 3 << std::endl;
    std::cout << "Observed: " << set_map[set_c] << std::endl;

    std::cout << "Evaluating set_map at set D" << std::endl;
    std::cout << "Expected: " << set_map[set_a] << std::endl;
    std::cout << "Observed: " << set_map[set_d] << std::endl;

    std::cout << "Evaluating set_map at set E" << std::endl;
    std::cout << "Expected: " << set_map[set_a] << std::endl;
    std::cout << "Observed: " << set_map[set_e] << std::endl;

    /*
     Simulation operations
    */

    /*
    Utils::Print::print_title("Pairwise Independent Bits");
    std::vector<int> p_bits = Simulation::Random::pairwise_random_bits(11);
    Utils::Print::print_vector(p_bits);

    Utils::Print::print_title("5-wise Independent Bits");
    std::vector<int> bits = Simulation::Random::kwise_random_bits(5, 11);
    Utils::Print::print_vector(bits);
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

    Utils::Print::print_title("Comparing Fibonacci");

    int test_number = 100000;
    Test::Comparison::ComparisonResult result1 =
        Test::Comparison::compare(
            Number::Fibonacci::fibonacci_dynamic_programming,
            Number::Fibonacci::fibonacci_closed_form, test_number);

    std::cout << "Fibonocci Dynamic Programming" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result1.first_time_millis << std::endl;
    std::cout << "Variance (ms): " << result1.first_variance << std::endl;

    std::cout << "Fibonocci Closed Form" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result1.second_time_millis << std::endl;
    std::cout << "Variance (ms): " << result1.second_variance << std::endl;

    Utils::Print::print_title("Comparing Steiner Tree");
    CostMatUndirGraph ex_stm_graph;
    ex_stm_graph.graph = CostMatGraph{{NO_EDGE, 5, 3, 6, 1, 3, 4},
                                      {5, NO_EDGE, 3, 6, 1, 3, 4},
                                      {3, 3, NO_EDGE, 6, 1, 3, 4},
                                      {6, 6, 6, NO_EDGE, 1, 3, 4},
                                      {1, 1, 1, 1, NO_EDGE, 3, 4},
                                      {3, 3, 3, 3, 3, NO_EDGE, 4},
                                      {4, 4, 4, 4, 4, 4, NO_EDGE}};
    Verticies ex_terminals = Verticies{1, 3, 4, 5};

    Test::Comparison::ComparisonResult result2 =
        Test::Comparison::compare(
            Graph::SteinerTree::steinertreemetric_approx_prims,
            Graph::SteinerTree::steinertreemetric_deterministic_dreyfus, ex_stm_graph, ex_terminals, 1000);

    std::cout << "Steiner Tree Metric Approximate Prims" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result2.first_time_millis << std::endl;
    std::cout << "Variance (ms): " << result2.first_variance << std::endl;

    std::cout << "Steiner Tree Metric Deterministic Dreyfus-Wagner" << std::endl;
    std::cout << "Input: " << test_number << std::endl;
    std::cout << "Average Time (ms): " << result2.second_time_millis << std::endl;
    std::cout << "Variance (ms): " << result2.second_variance << std::endl;

    /*
        Generating random vectors
    */

    Utils::Print::print_title("Generating Random Vectors");

    std::vector<int> arr1 = Simulation::Random::random_unique_ints_fisheryates(30, 10, 50);
    std::vector<int> arr2 = Simulation::Random::random_unique_ints_sort(30, 10, 50);

    // Utils::Print::print_vector<int>(arr1, " ");
    // Utils::Print::print_vector<int>(arr2, " ");

    Test::Comparison::ComparisonResult result3 =
        Test::Comparison::compare(
            Simulation::Random::random_unique_ints_fisheryates,
            Simulation::Random::random_unique_ints_sort, 3000, 1000, 5000, 1000);

    std::cout << "Random Uniuqe Int Array Fisher Yates" << std::endl;
    std::cout << "Average Time (ms): " << result3.first_time_millis << std::endl;
    std::cout << "Variance (ms): " << result3.first_variance << std::endl;

    std::cout << "Random Uniuqe Int Array Sort" << std::endl;
    std::cout << "Average Time (ms): " << result3.second_time_millis << std::endl;
    std::cout << "Variance (ms): " << result3.second_variance << std::endl;

    /*
        Generating Random GraphsComparison operations
    */
}