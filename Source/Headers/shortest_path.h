#pragma once
#include "adjacency_matrix.h"
#include "adjacency_list.h"
#include "binary_heap.h"

namespace GSP
{
    /// @brief const used as (contractual) infinity
    const int COST_INFINITY = INT_MAX;

    /// @brief Function will perform Dijkstra algorithm based on given AdjacencyMatrix
    /// @param matrix input matrix, it will not be modified
    /// @return table of predecessors. It needs to be later deleted
    int* Dijkstra(AdjacencyMatrix& matrix);

    /// @brief Function will perform Dijkstra algorithm based on given AdjacencyList
    /// @param list input list, it will not be modified
    /// @return table of predecessors. It needs to be later deleted
    int* Dijkstra(AdjacencyList& list);

    /// @brief Function will perform Bellman-Ford algorithm based on given AdjacencyMatrix
    /// @param matrix input matrix, it will not be modified
    /// @return table of predecessors. It needs to be later deleted
    int* BellmanFord(AdjacencyMatrix& matrix);

    /// @brief Function will perform Bellman-Ford algorithm based on given AdjacencyList
    /// @param list input list, it will not be modified
    /// @return table of predecessors. It needs to be later deleted
    int* BellmanFord(AdjacencyList& list);

    /// @brief
    /// @param matrix AdjacencyMatrix from which table was generated
    /// @param predecessorsArr valid table of predecessors
    /// @return table of predecessors as string
    std::string ToString(AdjacencyMatrix& matrix, int* predecessorsArr);

    /// @brief
    /// @param list AdjacencyList from which table was generated
    /// @param predecessorsArr valid table of predecessors
    /// @return table of predecessors as string
    std::string ToString(AdjacencyList& list, int* predecessorsArr);
}
