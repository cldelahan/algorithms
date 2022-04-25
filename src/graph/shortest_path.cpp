#include "shortest_path.h"

#include "../utils/print.h"

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

namespace Graph::ShortestPath
{

    /**
     * @brief Computes the shortest path between two verticies in a graph using Dijkstra's
     *        algorithm. Stops prematurely when the end vertex has been encountered.
     *
     * @param graph_struct The graph
     * @param start The starting vertex
     * @param end The ending vertex
     * @param path A reference to a path vector from start to end. Includes both start and end.
     *             Empty if there is no path
     * @return int The shortest path. NO_EDGE if there is no shortest path
     */
    int shortestpath_deterministic_dijkstras(CostMatUndirGraph graph_struct, Vertex start, Vertex end, Verticies &path)
    {
        CostMatGraph graph = graph_struct.graph;
        size_t n = graph.size();

        std::set<Vertex> unvisited;
        std::vector<int> tentative_distance(n, NO_EDGE);
        std::vector<int> previous(n, -1);
        for (size_t i = 0; i < n; i++)
        {
            unvisited.insert(i);
        }
        tentative_distance[start] = 0;

        Vertex current;
        // While we have not visited every vertex
        while (unvisited.size() > 0)
        {
            // Get smallest vertex by distance
            int min_dist = NO_EDGE;
            for (Vertex v : unvisited)
            {
                if (tentative_distance[v] <= min_dist)
                {
                    min_dist = tentative_distance[v];
                    current = v;
                }
            }

            // Stop early if it is our vertex
            if (current == end)
            {
                break;
            }

            unvisited.erase(current);

            // Update distances from smallest vertex
            for (Vertex v : unvisited)
            {
                // Can ignore but may have overflows
                if (graph[current][v] == NO_EDGE)
                {
                    continue;
                }
                // Cast to long to avoid overflow
                long new_dist = (long)tentative_distance[current] + graph[current][v];
                if (new_dist < tentative_distance[v])
                {
                    tentative_distance[v] = new_dist;
                    previous[v] = current;
                }
            }
        }

        // Return no path found
        if (tentative_distance[end] == NO_EDGE)
        {
            path = Verticies();
            return NO_EDGE;
        }

        // Regenerate the route from previous matrix
        Vertex c = previous[end];
        path.push_back(end);
        path.push_back(c);
        while (c != start)
        {
            c = previous[c];
            path.push_back(c);
        }

        std::reverse(path.begin(), path.end());
        return tentative_distance[end];
    }

    /**
     * @brief Computes the all-pairs shortest paths on the input graph using
     *          the Floyd-Warshall (a.k.a Roy-Warshall) algorithm. The algorithm
     *          runs in $|V|^3$ time and uses dynamic programming in
     *          determining the shortest path between (i, j) using the first
     *          1 vertex, 2 verticies, 3 verticies... until all nodes are
     *          considered.
     *
     * @param graph_struct An undirected graph that does not have any negative
     *          edges or cyles
     * @param shortest_path_tree A reference to the resultant shortest path
     *          tree, which can be used to determine the exact path that is
     *          shortest between two verticies (see shortestpath_treereconstruct)
     * @return CostMatGraph A cost matrix that holds the cost to get from any
     *          edge to another
     */
    CostMatGraph shortestpath_deterministic_floydwarshall(CostMatUndirGraph graph_struct, CostMatGraph &shortest_path_tree)
    {
        CostMatGraph graph = graph_struct.graph;
        size_t n = graph.size();

        // Define distances
        CostMatGraph dist = CostMatGraph(n, Verticies(n, NO_EDGE));
        shortest_path_tree = CostMatGraph(n, Verticies(n, NO_EDGE));
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                dist[i][j] = i == j ? 0 : graph[i][j];
                shortest_path_tree[i][j] = j;
            }
        }

        for (size_t k = 0; k < n; k++)
        { // Iteration of DP
            for (size_t i = 0; i < n; i++)
            { // i, j indicies
                for (size_t j = 0; j < n; j++)
                {
                    if (dist[i][k] != NO_EDGE && dist[k][j] != NO_EDGE && dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        shortest_path_tree[i][j] = shortest_path_tree[i][k];
                    }
                }
            }
        }
        return dist;
    }

    /**
     * @brief Using a shortest path tree, determine what is the shortest path
     *          from a start vertex to an end vertex
     *
     * @param shortest_path_tree The shortest path tree representation for
     *          example as returned in the Floyd-Warshall algorithm
     * @param start The start vertex to determine the path
     * @param end The end vertex
     * @return Verticies An vector of verticies for the path. Is empty if
     *          no path exists. Includes start and end.
     */
    Verticies shortestpath_treereconstruct(CostMatGraph shortest_path_tree, Vertex start, Vertex end)
    {
        Verticies path = Verticies();
        if (shortest_path_tree[start][end] == NO_EDGE)
        {
            return path;
        }
        path.push_back(start);
        while (start != end)
        {
            start = shortest_path_tree[start][end];
            path.push_back(start);
        }
        return path;
    }

}
