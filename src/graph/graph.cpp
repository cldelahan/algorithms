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

}