#pragma once

/// @brief Disjoint sets data structure
class DisjointSets
{
private:
    int* arr;
    int size;
public:
    DisjointSets(int size);
    ~DisjointSets();

    /// @brief Function will find representative of given subset 
    /// @param index index to get representative of
    /// @return representative
    int Find(int index);

    /// @brief Function will check if given elements are in same set. If no it will connect these to subsets
    /// @param elem1 
    /// @param elem2 
    /// @return true if elements were id different sets, false otherwise
    bool Union(int elem1, int elem2);
};
