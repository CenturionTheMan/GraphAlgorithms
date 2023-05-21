#pragma once
#include "adjacency_list.h"
#include "adjacency_matrix.h"
#include "ms_tree.h"
#include "shortest_path.h"
#include "helpers.h"

namespace Tester
{
    /// @brief SOME CONST
    const int MAX_WEIGHT = 1000; //max possible weight of edge
    const std::string OutputDirectory = "G:\\My Drive\\Studia\\Studia_sem_4\\SDiZO\\projekt\\Projekt2\\Sprawozdanie\\Tests\\"; 

    /// @brief Function will write given params to csv file in @ref OutputDirectory 
    /// @param pathSuffix name of file in OutputDirectory
    /// @param vertexAmount vertex amount in given test
    /// @param density density of graph in given test
    /// @param time time taken
    void WriteLineToFile(std::string pathSuffix, int vertexAmount, float density, double time);

    /// @brief Function will setup graph
    /// @param matrix graph to set
    /// @param vertexAmount vertex amount to set
    /// @param density density to set (will be filled with random wights)
    /// @param isDirected whether graph is directed
    /// @param isNegative whether weights can be negative
    void SetupGraph(AdjacencyMatrix& matrix, int vertexAmount, float density, bool isDirected, bool isNegative);

    /// @brief Function will setup graph
    /// @param matrix graph to set
    /// @param vertexAmount vertex amount to set
    /// @param density density to set (will be filled with random wights)
    /// @param isDirected whether graph is directed
    /// @param isNegative whether weights can be negative
    void SetupGraph(AdjacencyList& list, int vertexAmount, float density, bool isDirected, bool isNegative);


    /// @brief Function will perform test for Kruskal algorithm and adjacency matrix. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void MatrixKruskalTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Prima algorithm and adjacency matrix. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void MatrixPrimaTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Dijkstra algorithm and adjacency matrix. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void MatrixDijkstraTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Bellman-Ford algorithm and adjacency matrix. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void MatrixBellmanFordTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Kruskal algorithm and adjacency list. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void ListKruskalTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Prima algorithm and adjacency list. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void ListPrimaTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Dijkstra algorithm and adjacency list. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void ListDijkstraTest(int maxVertexAmount, int samplesAmount, int repsForAvg);

    /// @brief Function will perform test for Bellman-Ford algorithm and adjacency list. Will write result to file
    /// @param minVertexAmount min vertex amount in tets
    /// @param maxVertexAmount max vertex amount in test
    /// @param samplesAmount how many samples should be produced
    /// @param repsForAvg how many times should test be repeated
    void ListBellmanFordTest(int maxVertexAmount, int samplesAmount, int repsForAvg);
} 
