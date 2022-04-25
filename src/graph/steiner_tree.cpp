#include "steiner_tree.h"

#include "../utils/print.h"
#include "../set/set.h"
#include "minimum_spanning_tree.h"
#include "shortest_path.h"

#include <set>
#include <map>
#include <algorithm>

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

    /**
     * @brief Computes the same approximation as the steinertreemetric_approx_prims function,
     *      only now first converting the graph to a metric graph before doing so, and
     *      converting back afterwards. This requires converting all non-metric-compliant edges
     *      to their equialivent shortest paths, then running the steinertreemetric_approx_prims
     *      algorithm on the revised graph, and expanding
     *
     * @param graph_struct
     * @param terminals
     * @return CostMatUndirGraph
     */
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
    int steinertreemetric_deterministic_dreyfus(CostMatUndirGraph graph_struct, Verticies terminals)
    {
        /*
            It is worth noting, the implementation below gives its best
            effort to follow the the naming and syntatical conventions
            found in the original paper, including some no-longer
            typical naming / capitalization.
        */

        // throw "Not yet implemented";
        CostMatGraph graph = graph_struct.graph;
        size_t n = graph.size();

        /*
            As used in the paper, D(i, j) = length of shortest path
            in G from i to j. In our case, we can solve for D(i, j)
            by referencing shortest_paths[i][j], and actually compute
            the path using ShortestPath::
            shortestpath_treereconstruct(shortest_path_tree, i, j);
        */
        CostMatGraph shortest_path_tree;
        CostMatGraph shortest_paths = ShortestPath::shortestpath_deterministic_floydwarshall(graph_struct, shortest_path_tree);

        // Steiner terminals as a set
        std::set<Vertex> Y(terminals.begin(), terminals.end());
        // Initial terminal to optimize for
        Vertex q = terminals[0];

        // C has the same meaning as the paper; the set of steiner nodes not including our initial guess q
        std::set<Vertex> C = Y;
        C.erase(q);

        // All verticies in graph
        // TODO: Is there an easier array to insert n elements into a set
        std::set<Vertex> N = std::set<Vertex>();
        for (size_t i = 0; i < n; i++)
        {
            N.insert(i);
        }

        /*
            The paper references S_k(D) = the minimum steiner tree which
            involves connecting node k to two partitions of D, E and F.
            This is NOT the minimum steiner distance of D using k, but
            rather a similar value. The minimum steiner distance is
            computed by minimizing the d_lk + S_k(D) over all nodes k.

            The algorithm maintains a map S[D, i] -> a distance, which is
            indexed by set D and integer i. We implement this by creating
            S as a std::map mapping a std::set to a std::vector, where the
            i-th entry is our desired S[D, i]
        */
        std::map<std::set<Vertex>, Verticies> S;

        for (Vertex t : C) // paper Line 1
        {
            S[{t}] = Verticies(n, MAX_EDGE_COST);
            for (Vertex J : N) // paper Line 2
            {
                S[{t}][J] = shortest_paths[t][J]; // paper Line 3
            }
        }

        for (size_t m = 2; m <= C.size() - 1; m++) // Paper line 4
        {
            auto vector_of_sets = Set::get_subsets_of_size_n(C, m);
            for (std::set<Vertex> D : vector_of_sets) // Paper line 5
            {
                S[D] = Verticies(n, MAX_EDGE_COST); // Paper line 6, 7
                for (Vertex J : N)                  // Paper line 8
                {
                    int u = MAX_EDGE_COST; // Paper line 9
                    // In the paper, D[1] refers to the first element
                    // of the ordered set D
                    int d_one = *D.begin();
                    auto subsets = Set::get_all_subsets(D, {d_one});
                    for (std::set<Vertex> E : subsets) // Paper line 10
                    {
                        std::set<Vertex> D_minus_E;
                        std::set_difference(D.begin(), D.end(), E.begin(), E.end(),
                                            std::inserter(D_minus_E, D_minus_E.begin()));
                        int con_cost = S[E][J] + S[D_minus_E][J]; // Paper line 11
                        if (con_cost < u)
                        {
                            u = con_cost;
                        }
                    }
                    for (Vertex I : N) // Paper line 12
                    {
                        S[D][I] = std::min(S[D][I], shortest_paths[I][J] + u); // Paper line 13
                    }
                }
            }
        }
        int v = MAX_EDGE_COST; // Paper line 15
        for (Vertex J : N)     // Paper line 16
        {
            int u = MAX_EDGE_COST; // Paper line 17
            // In the paper, C[1] refers to the first element
            // of the ordered set C
            int c_one = *C.begin();
            auto subsets = Set::get_all_subsets(C, {c_one});
            for (std::set<Vertex> E : subsets) // Paper line 18
            {
                std::set<Vertex> C_minus_E;
                std::set_difference(C.begin(), C.end(), E.begin(), E.end(),
                                    std::inserter(C_minus_E, C_minus_E.begin()));
                u = std::min(u, S[E][J] + S[C_minus_E][J]); // Paper line 19
            }
            v = std::min(v, shortest_paths[q][J] + u);
        }
        return v;
    }
}