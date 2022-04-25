/**
 * @file print.h
 * @author Conner Delahanty (cldelahan@gmail.com)
 * @brief Contains helper functions for printing common types, including
 *      matricies, vectors, and others.
 *      NOTE: The functions are defined in this header file because
 *      using templates required either moving the implementation code
 *      to the header or explicitally instanciating the templates in the cpp
 *      (and I chose the former).
 *      As a result, the functions must also be denoted `inline` since
 *      the linker would complain about multiple definitions if two
 *      separate files import the print.h
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ALGO_SRC_UTILS_PRINT
#define ALGO_SRC_UTILS_PRINT

#include <vector>
#include <string>
#include <iostream>
#include <set>

namespace Utils::Print
{

    /**
     * @brief Prints the elements of a set
     *
     * @tparam T The type of each element
     * @param set The set to print
     * @param prefix String to prefix each element
     * @param suffix String to suffix each element
     */
    template <typename T>
    inline void print_set(std::set<T> set, std::string prefix = "", std::string suffix = "")
    {
        for (T v : set)
        {
            std::cout << prefix << v << suffix;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints the elements of a set, ignoring certain values
     *
     * @tparam T The type of each element
     * @param set The set to print
     * @param ignore Values in the set to ignore
     * @param prefix String to prefix each element
     * @param suffix String to suffix each element
     */
    template <typename T>
    inline void print_set(std::set<T> set, T ignore, std::string prefix = "", std::string suffix = "")
    {
        for (T v : set)
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
     * @brief Prints a vector of any type
     *
     * @tparam T The type of each element
     * @param vec The vector with values to print
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    template <typename T>
    inline void print_vector(std::vector<T> vec, std::string prefix = "", std::string suffix = "")
    {
        for (T v : vec)
        {
            std::cout << prefix << v << suffix;
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prints a vector of any type, allowing to ignore certain values
     *
     * @tparam T The type of each element
     * @param vec The vector with values to print
     * @param ignore Value to ignore, replaces with a underscore character
     * @param prefix A prefix to print after each entry
     * @param suffix A suffix to print after each entry
     */
    template <typename T>
    inline void print_vector(std::vector<T> vec, T ignore, std::string prefix = "", std::string suffix = "")
    {
        for (T v : vec)
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
     * @brief Prints a matrix of any type
     *
     * @tparam T The type of each element
     * @param mat The matrix with values to print
     * @param suffix A suffix to print after each entry
     */
    template <typename T>
    inline void print_matrix(std::vector<std::vector<T>> mat, std::string suffix = "")
    {
        for (std::vector<T> v : mat)
        {
            print_vector(v, "", suffix);
            std::cout << std::endl;
        }
    }

    /**
     * @brief Prints a matrix of any type, allowing to ignore certain values
     *
     * @tparam T The type of each element
     * @param mec The matrix with values to print
     * @param ignore Values to not print
     * @param suffix A suffix to print after each entry
     */
    template <typename T>
    inline void print_matrix(std::vector<std::vector<T>> mat, T ignore, std::string suffix = "")
    {
        for (std::vector<T> v : mat)
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
    inline void print_title(std::string title)
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

#endif