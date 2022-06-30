#ifndef ALGO_TEST_GRAPH_GEN
#define ALGO_TEST_GRAPH_GEN

#include "../../src/graph/graph.h"

namespace Test::Generator
{
    Graph::CostMatDirGraph generate_uniform_costmatdir_graph(int n_verticies, int n_edges);
    Graph::CostMatUndirGraph generate_uniform_costmatundir_graph(int n_verticies, int n_edges);
}

#endif