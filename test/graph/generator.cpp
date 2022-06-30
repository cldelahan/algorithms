#include <iostream>
#include <cmath>

#include "generator.h"
#include "../../src/simulation/random.h"

using namespace Graph;

namespace Test::Generator
{
    /**
     * @brief Randomly generate a Directed Cost-Matrix (each cost is 1)
     *      having specified the number of verticies and edges. Edges
     *      are placed uniformly at random. The cost is always one
     *
     * @param n_verticies The number of verticies to generate
     * @param n_edges The number of edges to generate
     * @return CostMatDirGraph The directed cost matrix graph
     */
    CostMatDirGraph generate_uniform_costmatdir_graph(int n_verticies, int n_edges)
    {
        CostMatGraph graph = CostMatGraph(n_verticies, Verticies(n_verticies, NO_EDGE));
        // Randomly generate unique values from [0, n_verticies^2)
        std::vector<int> ij_indicies = Simulation::Random::random_unique_ints_sort(n_edges, 0, n_verticies * n_verticies);

        for (int ij : ij_indicies)
        {
            graph[ij / n_verticies][ij % n_verticies] = 1;
        }
        CostMatDirGraph output;
        output.graph = graph;
        return output;
    }

    /**
     * @brief Randomly generate a Undirected Cost-Matrix (each cost is 1)
     *      having specified the number of verticies and edges. Edges
     *      are placed uniformly at random. The cost is always one
     *
     * @param n_verticies The number of verticies to generate
     * @param n_edges The number of edges to generate
     * @return CostMatUndirGraph The directed cost matrix graph
     */
    CostMatUndirGraph generate_uniform_costmatundir_graph(int n_verticies, int n_edges)
    {
        CostMatGraph graph = CostMatGraph(n_verticies, Verticies(n_verticies, NO_EDGE));
        // Randomly generate unique values from [0, n_verticies choose 2)
        int n_choose_2 = n_verticies * (n_verticies + 1) / 2;
        std::vector<int> ij_indicies = Simulation::Random::random_unique_ints_sort(n_edges, 0, n_choose_2);

        for (int ij : ij_indicies)
        {
            // Directed graphs are upper triangular
            // Counting from bottom
            int ij_b = n_choose_2 - ij;
            // Solve quadratic equation for which row
            // r^2 + r - 2 * ij_b = 0
            int det = 1 + 8 * ij_b;
            int row_b = (int)std::ceil((-1 + std::sqrt(det)) / 2.);
            int row_end_index = row_b * (row_b + 1) / 2;
            int col_b = row_b - (row_end_index - ij_b + 1);

            int row = n_verticies - row_b;
            int col = n_verticies - col_b;

            graph[row][col] = 1;
        }
        CostMatUndirGraph output;
        output.graph = graph;
        return output;
    }
}