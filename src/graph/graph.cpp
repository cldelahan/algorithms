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
    CostMatGraph induce_subgraph(CostMatGraph graph, Verticies on_verticies)
    {
        size_t v = on_verticies.size();
        CostMatGraph subgraph = CostMatGraph(v, Verticies(v, 0));

        // Populate subgraph with edges from vertex
        Vertex vi, vj;
        for (size_t i = 0; i < v; i++)
        {
            vi = on_verticies[i];
            for (size_t j = 0; j < v; j++)
            {
                vj = on_verticies[j];
                subgraph[i][j] = graph[vi][vj];
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
    bool is_metric(CostMatGraph graph)
    {
        // TODO: Find faster way than n^3?

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
}