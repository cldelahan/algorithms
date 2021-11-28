#include "graph.h"

#include <iostream>

namespace Graph
{
    /**
     * @brief Induces a subgraph on graph by verticies on_verticies with the corresponding
     *      costs and edges. 
     * @param graph The graph to sample using on_verticies
     * @param on_verticies The verticies (corresponding to indicies in the graph matrix) on
     *      which to induce the graph. The ith entry will be the ith row in the graph.
     * @return CostMatGraph A graph adjency matrix with the same size as on_verticies
     */
    CostMatUndirGraph induce_subgraph(CostMatUndirGraph graph_struct, Verticies on_verticies)
    {
        CostMatGraph graph = graph_struct.graph;
        size_t v = on_verticies.size();
        CostMatUndirGraph subgraph;
        subgraph.graph = CostMatGraph(v, Verticies(v, 0));

        // Populate subgraph with edges from vertex
        Vertex vi, vj;
        for (size_t i = 0; i < v; i++)
        {
            vi = on_verticies[i];
            for (size_t j = 0; j < v; j++)
            {
                vj = on_verticies[j];
                subgraph.graph[i][j] = graph[vi][vj];
            }
        }
        return subgraph;
    }

    /**
     * @brief Determines whether a passed graph is a metric, namely is a complete graph and the
     *      the triangle inequality holds. 
     * 
     * @param graph An undirected graph on which to determine is a metric
     * @return bool Whether the graph is a metric or not
     */
    bool is_metric(CostMatUndirGraph graph_struct)
    {
        // TODO: Find faster way than n^3?
        CostMatGraph graph = graph_struct.graph;

        size_t v = graph.size();

        int e1_cost = 0;
        int e2_cost = 0;

        // Iterate over all edge combos (i,j) and (j,k)
        for (size_t i = 0; i < v; i++)
        {
            for (size_t j = i + 1; j < v; j++)
            {
                e1_cost = graph[i][j];
                for (size_t k = j + 1; k < v; k++)
                {
                    e2_cost = graph[j][k];
                    // Check that there is always an edge
                    if (e1_cost == NO_EDGE || e2_cost == NO_EDGE || graph[i][k] == NO_EDGE)
                    {
                        return false;
                    }
                    // Check that graph is non-directed, namely that edge (i, j) = edge (j, i)
                    if (graph[i][j] != graph[j][i])
                    {
                        return false;
                    }
                    // Check that triangle inequality holds
                    if (e1_cost + e2_cost < graph[i][k])
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    /**
     * @brief Helper function to get the cost of CostMatGraph. Not to be exported
     * 
     * @param graph Graph in matrix form
     * @return int Sum of edges
     */
    int edge_cost_(CostMatGraph graph)
    {
        int v = graph.size();
        int sum = 0;
        for (int i = 0; i < v; i++)
        {
            for (int j = 0; j < v; j++)
            {
                if (graph[i][j] != NO_EDGE)
                {
                    sum += graph[i][j];
                }
            }
        }
        return sum;
    }

    /**
     * @brief Computes and returns the sum of all edge costs in a graph. If the graph is a tree, this
     *      is the cost of connection. Used to validate algorithms that seek to minimize this value.
     * 
     * @param graph_struct An undirected graph who's i,j-th elements is the cost between edge i and j. Doesn't need
     *      to be a tree
     * @return int The sum cost of all edges
     */
    int edge_cost(CostMatUndirGraph graph_struct)
    {
        // TODO: Watch out for integer overflows if costs are too large

        CostMatGraph graph = graph_struct.graph;
        int sum = edge_cost_(graph);
        return sum / 2;
    }

    /**
     * @brief Computes and returns the sum of all edge costs in a graph. If the graph is a tree, this
     *      is the cost of connection. Used to validate algorithms that seek to minimize this value.
     * 
     * @param graph_struct An directed graph who's i,j-th elements is the cost between edge i and j. Doesn't need
     *      to be a tree
     * @return int The sum cost of all edges
     */
    int edge_cost(CostMatDirGraph graph_struct)
    {
        // TODO: Watch out for integer overflow if costs are too large

        CostMatGraph graph = graph_struct.graph;
        int sum = edge_cost_(graph);
        return sum;
    }

}