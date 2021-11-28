#include "steiner_tree.h"

#include "../utils/print.h"
#include "minimum_spanning_tree.h"

namespace Graph::SteinerTree
{

    /**
     * @brief Computes a $2 - \frac{1}{|T|}$-approximation to the Steiner Tree problem on 
     *      metric graphs by computing the MST (Prims) on the subgraph induced by the terminals.
     * 
     * @param graph A metric graph (all edges exist and triangle equality holds)
     * @param terminals The steiner terminals which we seek to connect
     * @return CostMatGraph A graph that spans all of the terminals
     */
    CostMatUndirGraph steinertreemetric_approx_prims(CostMatUndirGraph graph_struct, Verticies terminals)
    {
        CostMatGraph graph = graph_struct.graph;
        // Create a graph induced by verticies and returns Prims on it
        CostMatUndirGraph subgraph = induce_subgraph(graph_struct, terminals);

        CostMatUndirGraph mst = MinimumSpanningTree::mst_deterministic_prims(subgraph);
        // Expand out subgraph mst to be the same size as graph
        size_t v = graph.size();
        size_t sub_v = subgraph.graph.size();

        CostMatUndirGraph output;
        output.graph = CostMatGraph(v, Verticies(v, NO_EDGE));
        Vertex vi, vj;
        for (size_t i = 0; i < sub_v; i++)
        {
            vi = terminals[i];
            for (size_t j = 0; j < sub_v; j++)
            {
                vj = terminals[j];
                output.graph[vi][vj] = mst.graph[i][j];
                output.graph[vj][vi] = mst.graph[i][j];
            }
        }
        return output;
    }

}