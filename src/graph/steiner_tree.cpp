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

    CostMatUndirGraph steinertree_approx_prims(CostMatUndirGraph graph_struct, Verticies terminals)
    {
        // First compute all-pairs shortest path
        throw "Not yet implemented";
    }

    /**
     * @brief Compute the solution to the steiner tree problem using the famous 1971 algorithm by
     *      Dreyfus and Wagner. The algorithm correctly solves the Stiner problem through solving for
     *      successive optimal subsets to minimize length. The algorithm runs in 
     *      $n^3 / 2 + n^2(2^{k-1} - k - 1) + n(3^{k-1} - 2^k + 2) / 2$ time where n is the number
     *      of verticies and k is the number of steiner terminals.
     * 
     * @cite author = {Dreyfus, S. E. and Wagner, R. A.},
     *       title = {The steiner problem in graphs},
     *       journal = {Networks},
     *       volume = {1},
     *       number = {3},
     *       pages = {195-207},
     *       doi = {https://doi.org/10.1002/net.3230010302},
     *       url = {https://onlinelibrary.wiley.com/doi/abs/10.1002/net.3230010302},
     *       eprint = {https://onlinelibrary.wiley.com/doi/pdf/10.1002/net.3230010302},
     *       abstract = {Abstract An algorithm for solving the Steiner problem on a finite undirected graph is presented. 
     *                  This algorithm computes the set of graph arcs of minimum total length needed to connect a specified 
     *                  set of k graph nodes. If the entire graph contains n nodes, the algorithm requires time proportional 
     *                  to n3/2 + n2 (2k-1 - k - 1) + n(3k-1 - 2k + 3)/2. The time requirement above includes the term n3/2, 
     *                  which can be eliminated if the set of shortest paths connecting each pair of nodes in the graph is available.},
     *       year = {1971}
     * 
     * @param graph A metric graph (all edges exist and triangle equality holds)
     * @param terminals The steiner terminals which we seek to connect
     * @return CostMatUndirGraph A graph that spans all of the terminals
     */
    CostMatUndirGraph steinertreemetric_deterministic_dreyfus(CostMatUndirGraph graph_struct, Verticies terminals)
    {
        throw "Not yet implemented";
    }
}