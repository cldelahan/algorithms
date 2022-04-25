#ifndef ALGO_SRC_GRAPH_STEINERTREE
#define ALGO_SRC_GRAPH_STEINERTREE

#include "graph.h"

namespace Graph::SteinerTree
{
    // CostMat steinertreemetric_bruteforce(CostMat, Verticies);
    CostMatUndirGraph steinertreemetric_approx_prims(CostMatUndirGraph, Verticies);
    CostMatUndirGraph steinertree_approx_prims(CostMatUndirGraph, Verticies);
    int steinertreemetric_deterministic_dreyfus(CostMatUndirGraph, Verticies);
}

#endif