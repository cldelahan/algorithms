#ifndef ALGO_SRC_SET
#define ALGO_SRC_SEC

#include <set>
#include <vector>

namespace Set
{
    std::vector<std::set<int>> get_subsets_of_size_n(std::set<int>, size_t);
    std::vector<std::set<int>> get_all_subsets(std::set<int>, std::vector<int> = {}, std::vector<int> = {});
}

#endif