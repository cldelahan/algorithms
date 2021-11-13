#include <time.h>
#include <iostream>
#include <stdlib.h>

#include <string>
#include <vector>

namespace Utils::Print
{
    /**
     * @brief Prints a vector
     * 
     * @param vec The vector with values to print
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    void print_vector(std::vector<float> vec, std::string prefix = "", std::string suffix = ", ")
    {
        for (float v : vec)
        {
            std::cout << prefix << v << suffix;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a vector
     * 
     * @param vec The vector with values to print
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    void print_vector(std::vector<int> vec, std::string prefix = "", std::string suffix = ", ")
    {
        for (int v : vec)
        {
            std::cout << prefix << v << suffix;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a matrix
     * 
     * @param vec The matrix with values to print
     * @param prefix A prefix to print after each entry
     */
    void print_matrix(std::vector<std::vector<float>> mat, std::string prefix = "")
    {
        for (std::vector<float> v : mat)
        {
            print_vector(v, prefix);
            std::cout << std::endl;
        }
    }

    /**
     * @brief Prints a matrix
     * 
     * @param vec The matrix with values to print
     * @param prefix A prefix to print after each entry
     */
    void print_matrix(std::vector<std::vector<int>> mat, std::string prefix = "")
    {
        for (std::vector<int> v : mat)
        {
            print_vector(v, prefix);
        }
        std::cout << std::endl;
    }

}