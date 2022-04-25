#include <algorithm>
#include <set>
#include <vector>
#include <iostream>

#include "set.h"

namespace Set
{
    /**
     * @brief From a set, returns a vector of all unique subsets of size n
     *
     * @param set The set
     * @param n The size of each returned subset
     * @return std::vector<std::set<int>> The returned vector of sets
     */
    std::vector<std::set<int>> get_subsets_of_size_n(std::set<int> set, size_t n)
    {
        std::vector<int> mask = std::vector<int>();
        for (size_t i = 0; i < set.size(); i++)
        {
            if (i < set.size() - n)
            {
                mask.push_back(0);
            }
            else
            {
                mask.push_back(1);
            }
        }

        std::vector<std::set<int>> output;
        std::set<int> temp;
        int count;
        do
        {
            count = 0;
            temp = std::set<int>();
            for (int val : set)
            {
                if (mask[count] == 1)
                {
                    temp.insert(val);
                }
                count++;
            }
            output.push_back(temp);
        } while (std::next_permutation(mask.begin(), mask.end()));
        return output;
    }

    /**
     * @brief From a set, return all possible subsets of the set, not including itself
     *
     * @param set The set
     * @param must_include_values A vector of values that must be included in each subset. Most oftentimes is empty
     * @param must_exclude_values A vector of values that must be excluded in each subset. Most oftentimes is empty
     * @return std::vector<std::set<int>> The returned vector of sets
     */
    std::vector<std::set<int>> get_all_subsets(std::set<int> set,
                                               std::vector<int> must_include_values,
                                               std::vector<int> must_exclude_values)
    {
        // We first remove the exclude values
        for (int value : must_exclude_values)
        {
            set.erase(value);
        }
        // We first remove these values, then add them after
        for (int value : must_include_values)
        {
            set.erase(value);
        }
        std::vector<std::set<int>> output = std::vector<std::set<int>>();
        output.push_back({});
        for (size_t subset_size = 1; subset_size < set.size(); subset_size++)
        {
            std::vector<std::set<int>> subset = Set::get_subsets_of_size_n(set, subset_size);
            // Reserve pre-allocates space
            output.reserve(output.size() + subset.size());
            // Extend the output vector
            output.insert(output.end(), subset.begin(), subset.end());
        }
        // Re-include the required values
        for (size_t index = 0; index < output.size(); index++)
        {
            for (int v : must_include_values)
            {
                output[index].insert(v);
            }
        }
        return output;
    }
}