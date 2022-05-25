#include <iostream>

#include "generator.h"
#include "../../src/graph/minimum_spanning_tree.h"

namespace Gaph::Test::Generator
{
    Graph::CostMatDirGraph generate_costmatdir_graph(int n_verticies, int n_edges)
    {
        Graph::CostMatUndirGraph g;
        Graph::MinimumSpanningTree::mst_deterministic_prims(g);
        Graph::CostMatDirGraph h;
        return h;
    }
}