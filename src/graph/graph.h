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

    // TODO: May need to define struct graphs as pointers

    // No edge is present between two verticies
    const int NO_EDGE = INT_MAX;
    // Distinguishing between no edge (infinity) and a really large edge cost
    const int MAX_EDGE_COST = (INT_MAX - 1) / 2;

    // Common typedefs for readability
    typedef int Vertex;
    typedef std::vector<Vertex> Verticies;
    typedef std::pair<Vertex, Vertex> Edge;
    typedef std::vector<Edge> Edges;

    /*
        Graphs are represented as singleton structs with a single graph parameter
        to
            1. Enforce that the algorithm and the graph make the same assumptions
            2. Have greater transparency as to the output of an algorithm 
        where typedef-ing alone is not sufficient since different representations
        may employ the same type (i.e. directed and undirected adjacency matricies) 

        It is relatively easy to cast between different representations, and some
        helper functions are provided to do that.

        The representations take the format of 
        <Type><Dir/Undir>Graph
        where the type is the representation, dir / undir refers to whether it
        is directed or undirected.
    */

    // Type of graph structure
    typedef std::vector<Verticies> AdjListGraph;
    typedef std::vector<std::vector<bool>> AdjMatGraph;
    typedef std::vector<std::vector<int>> CostMatGraph;
    typedef std::vector<std::pair<int, int>> EdgeListGraph;

    /*

    Commenting out implementation until they are supported

    struct AdjListDirGraph
    {
        // graph[i] is all nodes connected to i
        AdjListGraph graph;
    };

    struct AdjListUndirGraph
    {
        // graph[i] is all nodes connected to i
        AdjListGraph graph;
    };

    struct AdjMatDirGraph
    {
        // graph[i][j] = true if (i, j) is an edge
        AdjMatGraph graph;
    };

    struct AdjMatUndirGraph
    {
        // graph[i][j] = true if (i, j) is an edge. Is symmetric
        AdjMatGraph graph;
    };
    */

    struct CostMatDirGraph
    {
        // graph[i][j] = cost of edge (i, j). Is NO_EDGE if not an edge
        CostMatGraph graph;

        CostMatDirGraph()
        {
            graph = CostMatGraph();
        }

        CostMatDirGraph(CostMatGraph g)
        {
            graph = g;
        }

        /*
        CostMatDirGraph operator=(CostMatGraph other)
        {
            CostMatDirGraph c;
            c.graph = other;
            return c;
        }
        */
    };

    struct CostMatUndirGraph
    {
        // graph[i][j] = cost of edge (i, j). Is NO_EDGE if not an edge. Is symmetric
        CostMatGraph graph;

        CostMatUndirGraph()
        {
            graph = CostMatGraph();
        }

        CostMatUndirGraph(CostMatGraph g)
        {
            graph = g;
        }

        /*
        CostMatUndirGraph operator=(CostMatGraph other)
        {
            CostMatUndirGraph c;
            c.graph = other;
            return c;
        }
        */
    };

    struct EdgeListDirGraph
    {
        // List of edges between two verticies
        EdgeListGraph graph;

        EdgeListDirGraph()
        {
            graph = EdgeListGraph();
        }

        EdgeListDirGraph(EdgeListGraph g)
        {
            graph = g;
        }
    };

    struct EdgeListUndirGraph
    {
        /* 
            List of edges between two verticies.
            If edge (i, j) and (j, i) is in the graph and i < j
            then pair<i, j> is in the array    
        */
        EdgeListGraph graph;

        EdgeListUndirGraph()
        {
            graph = EdgeListGraph();
        }

        EdgeListUndirGraph(EdgeListGraph g)
        {
            graph = g;
        }
    };

    // Check graph properties
    bool is_metric(CostMatUndirGraph);

    // Get global graph properties
    int edge_cost(CostMatUndirGraph);

    // Convienient global graph functions
    CostMatUndirGraph induce_subgraph(CostMatUndirGraph, Verticies); // TODO: Make sure is not AdjListGraph

}

#endif