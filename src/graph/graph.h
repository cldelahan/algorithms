#ifndef ALGO_SRC_GRAPH
#define ALGO_SRC_GRAPH

#include <climits>
#include <utility>
#include <vector>

/*
    Contains global infom available for all header files
*/

namespace Graph
{
    // TODO: Need to separate directed (full matrix) and non-directed (upper triangular)
    // Defining typedefs for readability
    typedef int Vertex;
    typedef std::vector<Vertex> Verticies;
    typedef std::pair<Vertex, Vertex> Edge;
    typedef std::vector<Edge> Edges;
    // Defined independent of above since isn't really array of verticies
    typedef std::vector<std::vector<int>> AdjListGraph;
    typedef std::vector<std::vector<bool>> AdjMatGraph;
    typedef std::vector<std::vector<int>> CostMatGraph;
    typedef std::vector<std::pair<int, int>> EdgeListGraph;

    // Important Graph Constants for CostMatGraph
    const int NO_EDGE = INT_MAX;
    // Distinguishing between no edge (infinity) and a really large edge cost
    const int MAX_EDGE_COST = (INT_MAX - 1) / 2;

    // Check graph properties
    bool is_metric(CostMatGraph);

    // Get global graph properties
    int edge_cost(CostMatGraph);

    // Convienient global graph functions
    CostMatGraph induce_subgraph(CostMatGraph, Verticies); // TODO: Make sure is not AdjListGraph

}

#endif