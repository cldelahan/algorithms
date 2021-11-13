#ifndef ALGO_SRC_UTILS_PRINT
#define ALGO_SRC_UTILS_PRINT

#include <vector>
#include <string>

namespace Utils::Print
{
    void print_vector(std::vector<float>, std::string = "", std::string = "");
    void print_vector(std::vector<int>, std::string = "", std::string = "");
    void print_matrix(std::vector<std::vector<float>>, std::string = "");
    void print_matrix(std::vector<std::vector<int>>, std::string = "");
}

#endif