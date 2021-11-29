#ifndef ALGO_SRC_GRAPH_SHORTESTPATH
#define ALGO_SRC_GRAPH_SHORTESTPATH

#include "graph.h"
namespace Graph::ShortestPath
{

    int shortestpath_deterministic_dijkstras(CostMatUndirGraph, Vertex, Vertex, Verticies &);
    CostMatGraph shortestpath_deterministic_floydwarshall(CostMatUndirGraph, CostMatGraph &);
    Verticies shortestpath_treereconstruct(CostMatGraph, Vertex, Vertex);

}

#endif