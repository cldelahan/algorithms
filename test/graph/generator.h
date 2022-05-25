#ifndef ALGO_TEST_GRAPH_GEN
#define ALGO_TEST_GRAPH_GEN

#include "../../src/graph/graph.h"

namespace Graph::Test::Generator
{

    class EdgeGenerationStrategy
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

    Graph::CostMatDirGraph generate_uniform_costmatdir_graph(int n_verticies, int n_edges);
    Graph::CostMatUnDirGraph generate_uniform_costmatundir_graph(int n_verticies, int n_edges);
}

#endif