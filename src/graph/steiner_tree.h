#ifndef ALGO_SRC_GRAPH_STEINERTREE
#define ALGO_SRC_GRAPH_STEINERTREE

#include "graph.h"

namespace Graph::SteinerTree
{
    // CostMatGraph steinertreemetric_bruteforce(CostMatGraph, Verticies);
    CostMatUndirGraph steinertreemetric_approx_prims(CostMatUndirGraph, Verticies);
}

#endif