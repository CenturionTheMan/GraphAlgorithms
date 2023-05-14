#pragma once
#include "binary_heap.h"
#include "disjoint_sets.h"
#include "adjacency_matrix.h"
#include "adjacency_list.h"

namespace MST
{
    /// @brief Function will perform Kruskal algorithm based on given AdjacencyMatrix
    /// @param matrix input graph. Function will not modify it
    /// @return new graph which represents minimum spanning tree
    AdjacencyMatrix KruskalAlgorithm(AdjacencyMatrix& matrix);

    /// @brief Function will perform Kruskal algorithm based on given AdjacencyList
    /// @param list input graph. Function will not modify it
    /// @return new graph which represents minimum spanning tree
    AdjacencyList KruskalAlgorithm(AdjacencyList& list);

    /// @brief Function will perform Prima algorithm based on given AdjacencyMatrix
    /// @param matrix input graph. Function will not modify it
    /// @return new graph which represents minimum spanning tree
    AdjacencyMatrix PrimaAlgorithm(AdjacencyMatrix& matrix);

    /// @brief Function will perform Prima algorithm based on given AdjacencyList
    /// @param list input graph. Function will not modify it
    /// @return new graph which represents minimum spanning tree
    AdjacencyList PrimaAlgorithm(AdjacencyList& list);

    /// @brief Function will return minimum spanning tree as string
    /// @param matrix graph which represents minimum spanning tree
    /// @return result string
    std::string ToString(AdjacencyMatrix& matrix);

    /// @brief Function will return minimum spanning tree as string
    /// @param list graph which represents minimum spanning tree
    /// @return result string
    std::string ToString(AdjacencyList& list);
}