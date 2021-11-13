#ifndef ALGO_SRC_GRAPH
#define ALGO_SRC_GRAPH

#include <utility>
#include <vector>

/*
    Contains global infom available for all header files
*/

namespace Graph
{
    // Defining typedefs for readability
    typedef std::vector<std::vector<int>> AdjMatGraph;
    typedef std::vector<std::pair<int, int>> AdjListGraph;
}

#endif