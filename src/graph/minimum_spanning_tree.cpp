#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "minimum_spanning_tree.h"

namespace Graph::MinimumSpanningTree
{

    /**
     * @brief Returns the minimum spanning tree of a graph supplied as an adjacency matrix with
     *      graph[i][j] = cost((i,j)), and 0 if there is no such edge using Prim's MST Algorithm.
     *      Graph should be undirected, namely graph[i][j] = graph[j][i], but must be connected.
     * 
     * @param graph Symmetric matrix representing the adjacency matrix with non-zero entries being
     *      the cost of edge i,j.
     * @return std::vector<std::vector<int>> Adjacency matrix of minimum spanning tree. 
     */
    std::vector<std::vector<int>> mst_deterministic_prims(std::vector<std::vector<int>> graph)
    {
        size_t v = graph.size();

        std::set<int> v_in_mst;
        std::map<int, int> cost_to_connect;
        std::vector<int> parent(v, 0);

        std::vector<std::vector<int>> output(v, std::vector<int>(v, 0));

        // Initialize all verticies arb. far away from mst set
        for (size_t i = 1; i < v; i++)
        {
            cost_to_connect[i] = INT_MAX;
        }
        // Set first vertex close to be parent
        cost_to_connect[0] = 0;

        while (v_in_mst.size() != v)
        {
            // Find the closest vertex not in the MST
            // TODO. Use priority queue / heap
            int min_cost = INT_MAX;
            int min_index = 0;
            for (size_t i = 0; i < v; i++)
            {
                if (cost_to_connect[i] <= min_cost && v_in_mst.find(i) == v_in_mst.end())
                {
                    min_index = i;
                    min_cost = cost_to_connect[i];
                }
            }
            v_in_mst.insert(min_index);

            // Update how close all other verticies are to the MST
            for (size_t i = 0; i < v; i++)
            {
                if (graph[min_index][i] && graph[min_index][i] < cost_to_connect[i])
                {
                    cost_to_connect[i] = graph[min_index][i];
                    // Store the parent of each vertex in MST for ourput
                    parent[i] = min_index;
                }
            }
        }
        // Start at 1 since vertex 0 does not need parent assigned
        for (size_t i = 1; i < v; i++)
        {
            // Assign cost to be the original graph costs
            output[parent[i]][i] = graph[parent[i]][i];
        }
        return output;
    }
}