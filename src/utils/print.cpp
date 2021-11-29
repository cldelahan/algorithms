#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "./print.h"

namespace Utils::Print
{
    /**
     * @brief Prints a vector. TODO. Typedef these to have less functions
     * 
     * @param vec The vector with values to print
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    void print_vector(std::vector<float> vec, std::string prefix, std::string suffix)
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
    void print_vector(std::vector<int> vec, std::string prefix, std::string suffix)
    {
        for (int v : vec)
        {
            std::cout << prefix << v << suffix;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a vector
     * 
     * @param vec The vector with values to print
     * @param ignore Value to ignore, replaces with a underscore character
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    void print_vector(std::vector<int> vec, int ignore, std::string prefix, std::string suffix)
    {
        for (int v : vec)
        {
            if (v == ignore)
            {
                std::cout << prefix << "_" << suffix;
            }
            else
            {
                std::cout << prefix << v << suffix;
            }
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a matrix
     * 
     * @param mat The matrix with values to print
     * @param suffix A suffix to print after each entry
     */
    void print_matrix(std::vector<std::vector<float>> mat, std::string suffix)
    {
        for (std::vector<float> v : mat)
        {
            print_vector(v, "", suffix);
            std::cout << std::endl;
        }
    }

    /**
     * @brief Prints a matrix
     * 
     * @param mat The matrix with values to print
     * @param suffix A suffix to print after each entry
     */
    void print_matrix(std::vector<std::vector<int>> mat, std::string suffix)
    {
        for (std::vector<int> v : mat)
        {
            print_vector(v, "", suffix);
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a matrix
     * 
     * @param mec The matrix with values to print
     * @param ignore Values to not print
     * @param suffix A suffix to print after each entry
     */
    void print_matrix(std::vector<std::vector<int>> mat, int ignore, std::string suffix)
    {
        for (std::vector<int> v : mat)
        {
            print_vector(v, ignore, "", suffix);
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a title to standard out to be displayed. Used for debugging
     *          and to make it easy to read what a section does
     * 
     * @param title The string to print
     */
    void print_title(std::string title)
    {
        size_t l = title.length();
        for (size_t i = 0; i < l + 8; i++)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
        std::cout << "|   " << title << "   |" << std::endl;
        for (size_t i = 0; i < l + 8; i++)
        {
            std::cout << "-";
        }
        std::cout << std::endl;
    }

}