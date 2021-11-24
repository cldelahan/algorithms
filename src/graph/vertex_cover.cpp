#include "vertex_cover.h"

#include <iostream>
#include <set>
#include <utility>
#include <vector>

#include "../simulation/random.h"

namespace Graph::VertexCover
{

    /**
     * @brief Returns the naive 2-approximation to vertex cover on a graph. 
     *      Namely, will return a list of verticies such that each edge is 
     *      incident on one of the verticies. Will not check that graph is
     *      valid.
     * 
     * @param graph A graph (D / UD) represented as an adjacency matrix. Each 
     *      non-zero entry i,j is a directed edge between i and j. 
     * @return std::vector<int> 
     */
    std::set<int> vertex_cover_approx(EdgeListGraph edges)
    {
        std::set<int> vertex_cover;
        std::pair<int, int> edge;
        int index;

        std::size_t size = edges.size();
        while (size > 0)
        {
            // Randomly sample an edge
            index = Simulation::Random::random_int(0, size);
            edge = edges.at(index);
            // Store verticies in vertex cover
            vertex_cover.insert(edge.first);
            vertex_cover.insert(edge.second);
            // Remove all verticies incident on these verticies
            for (int i = edges.size() - 1; i >= 0; i--)
            {
                if (edges[i].first == edge.first || edges[i].second == edge.first ||
                    edges[i].first == edge.second || edges[i].second == edge.second)
                {
                    // Remove from list (swap with back and remove back)
                    // edges.erase(edges.begin() + i);
                    edges[i] = edges.back();
                    edges.pop_back();
                }
            }
            size = edges.size();
        }
        return vertex_cover;
    }
}