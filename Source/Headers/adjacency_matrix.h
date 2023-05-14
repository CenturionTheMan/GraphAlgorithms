#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <fstream>

/// @brief Graph representation as adjacency matrix
class AdjacencyMatrix
{
private:
    /// @brief double array of matrix
    int** arr;
    /// @brief vertex amount
    int sizeVertex;

    /// @brief begin vertex and end vertex (for algorithms)
    int beginVertex, endVertex;


    void Init();
    void RemoveAll();
    
public:
    /// @brief const used as (contractual) infinity
    static const int WEIGHT_INFINITY = INT_MAX;

    /// @brief CTORS / DTOR
    AdjacencyMatrix();
    AdjacencyMatrix(int vertexAmount);

    /// @brief Function will initialize graph using data from file
    /// @param filePath file path
    /// @param isTwoSided if false graph will de directed
    AdjacencyMatrix(std::string filePath, bool isTwoSided = false);
    ~AdjacencyMatrix();
    ///

    /// @brief Function will load data from file into graph
    /// @param filePath path for file
    /// @param isTwoSided if false graph will be directed
    /// @return true if success, false otherwise
    bool LoadDataFromFile(std::string filePath, bool isTwoSided = false);

    /// @brief Function will set vertex amount. Warning! - function will remove previously stored data
    /// @param amount size to set
    void SetVertexAmount(int amount);

    /// @brief Function will set connection (edge) between two vertexes
    /// @param vertexFrom Begin vertex
    /// @param vertexTo End vertex
    /// @param weight weight of new edge
    /// @param isTwoSided whether connection is in both direction
    /// @return true if success, false otherwise
    bool SetConnection(int vertexFrom, int vertexTo, int weight, bool isTwoSided = false);

    /// @brief Function will return weight of edge which is between given nodes
    /// @param fromVertex 
    /// @param toVertex 
    /// @exception function will raise exception if given vertexes are out of bands
    /// @return weight of given eg=dge
    int GetWeight(int fromVertex, int toVertex);

    /// @brief Function will set begin vertex and end vertex (used for algorithms)
    /// @param beginVertex
    /// @param endVertex 
    void SetBeginAndEndVertex(int beginVertex, int endVertex);

    /// @brief 
    /// @return end vertex of graph
    int GetEndVertex();

    /// @brief 
    /// @return begin vertex of graph
    int GetBeginVertex();

    /// @brief 
    /// @return amount of vertexes in graph
    int GetVertexAmount();

    /// @brief 
    /// @return graph as string
    std::string ToString();
};

