#ifndef ALGO_SRC_GRAPH_VERTEXCOVER
#define ALGO_SRC_GRAPH_VERTEXCOVER

#include <set>
#include <utility>
#include <vector>

namespace Graph::VertexCover
{
    std::set<int> vertex_cover_approx(std::vector<std::pair<int, int>>);
}

#endif