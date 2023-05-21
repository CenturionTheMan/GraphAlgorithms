#pragma once
#include <iostream>

struct SetElement
{
    SetElement* parent;
    int rank;

    SetElement()
    {
        this->rank = 0;
        parent = this;
    }
};


/// @brief Disjoint sets data structure
class DisjointSets
{
private:
    SetElement** sets;
    int size;
public:
    DisjointSets(int size);
    ~DisjointSets();

    /// @brief Function will find representative of given subset 
    /// @param index index to get representative of
    /// @return representative
    SetElement* Find(int index);

    /// @brief Function will check if given elements are in same sets. If no it will connect these to subsets
    /// @param elem1 
    /// @param elem2 
    /// @return true if elements were in different sets, false otherwise
    bool Union(int elem1, int elem2);
};
