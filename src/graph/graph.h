#ifndef ALGO_SRC_GRAPH
#define ALGO_SRC_GRAPH

#include <climits>
#include <utility>
#include <vector>

/*
    Contains global info available for all header files
*/

namespace Graph
{

    // TODO: May need to define struct graphs as pointers

    // No edge is present between two verticies
    const int NO_EDGE = INT_MAX;
    // Distinguishing between no edge (infinity) and a really large edge cost
    const int MAX_EDGE_COST = (INT_MAX - 1) / 2;
    // Invalid number of verticies or edges
    const int INVALID_NUM = INT_MIN;

    // Common typedefs for readability
    typedef int Vertex;
    typedef std::vector<Vertex> Verticies;
    typedef std::pair<Vertex, Vertex> Edge;
    typedef std::vector<Edge> Edges;
    typedef std::vector<std::vector<Verticies>> ShortestPaths;

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

    /**
     * @brief Graph is represented by a cost-matrix, where
     *      graph[i][j] = cost of edge (i, j). Value maxes at EDGE_MAX
     *      and is NO_EDGE if not an edge. Since is directed, it may be
     *      the case that graph[i][j] != graph[j][i].
     */
    struct CostMatDirGraph
    {
        CostMatGraph graph;

        /**
         * @brief Convenience default constructor
         */
        CostMatDirGraph()
        {
            graph = CostMatGraph();
        }

        /**
         * @brief Convenience constructor with a matrix
         */
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

    /**
     * @brief Graph is represented by a cost-matrix, where
     *      graph[i][j] = graph[j][i] =  cost of edge (i, j) = (j, i).
     *      Value maxes at EDGE_MAX and is NO_EDGE if not an edge.
     *      Since is non-directed, the graph is symmetric
     */
    struct CostMatUndirGraph
    {
        CostMatGraph graph;

        /**
         * @brief Convenience default constructor
         */
        CostMatUndirGraph()
        {
            graph = CostMatGraph();
        }

        /**
         * @brief Convenience constructor with matrix
         */
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

    /**
     * @brief Graph implemented as an edge list, which is directed. Namely,
     *      an array of edges where the order (i, j) matters. The edges
     *      do not intrinsically have a weight
     *
     */
    struct EdgeListDirGraph
    {
        EdgeListGraph graph;

        /**
         * @brief Convenience default constructor
         */
        EdgeListDirGraph()
        {
            graph = EdgeListGraph();
        }

        /**
         * @brief Convenience list constructor
         */
        EdgeListDirGraph(EdgeListGraph g)
        {
            graph = g;
        }
    };

    /**
     * @brief Graph implemented as an edge list, which is
     *      undirected. Namely, if edge (i, j) and (j, i) is
     *      in the graph, and i < j, then pair <i, j> is in the
     *      array. There are not duplicates.
     */
    struct EdgeListUndirGraph
    {
        EdgeListGraph graph;

        /**
         * @brief Convenience default constructor
         */
        EdgeListUndirGraph()
        {
            graph = EdgeListGraph();
        }

        /**
         * @brief Convenience list constructor
         */
        EdgeListUndirGraph(EdgeListGraph g)
        {
            graph = g;
        }
    };

    // Check graph properties
    bool is_metric(CostMatUndirGraph);

    // Get global graph properties
    int edge_cost(CostMatUndirGraph);
    int edge_cost(CostMatDirGraph);

    // Convienient global graph functions
    CostMatUndirGraph induce_subgraph(CostMatUndirGraph, Verticies); // TODO: Make sure is not AdjListGraph

}

#endif