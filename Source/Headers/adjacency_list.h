#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

/// @brief Struct used by AdjacencyList to store neighbors og given vertex
struct Connection
{
    Connection* nextConnection;
    int vertex;
    int weight;

    Connection()
    {

    }

    Connection(int vertex, int weight)
    {
        this->vertex = vertex;
        this->weight = weight;
        this->nextConnection = NULL;
    }
};

/// @brief Graph representation as adjacency list
class AdjacencyList
{
private:
    /// @brief Array of lists oc vertexes
    Connection** arr;
    /// @brief vertex amount in graph
    int size;

    /// @brief begin vertex and end vertex (for algorithms)
    int beginVertex, endVertex;

    /// @brief Function will initialize params
    void Init();

    /// @brief Function will free memory
    void RemoveAll();

public:
    /// @brief CTORS / DTOR
    AdjacencyList();
    AdjacencyList(int vertexAmount);
    
    /// @brief Function will initialize graph using data from file
    /// @param filePath file path
    /// @param isTwoSided if false graph will de directed
    AdjacencyList(std::string filePath, bool isTwoSided = false);
    ~AdjacencyList();
    //

    /// @brief Function will load data from file into graph
    /// @param filePath path for file
    /// @param isTwoSided if false graph will be directed
    /// @return true if success, false otherwise
    bool LoadDataFromFile(std::string filePath, bool isTwoSided = false);

    /// @brief Function will set vertex amount. Warning! - function will remove previously stored data
    /// @param size size to set
    void SetVertexAmount(int size);

    /// @brief Function will set connection (edge) between two vertexes
    /// @param fromVertex Begin vertex
    /// @param toVertex End vertex
    /// @param weight weight of new edge
    /// @param isTwoSided whether connection is in both direction
    /// @return true if success, false otherwise
    bool SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided = false);

    /// @brief Function will find edge between given vertexes
    /// @param fromVertex begin vertex
    /// @param toVertex end vertex
    /// @return pointer to given connection if exists, NULL otherwise
    Connection* FindConnection(int fromVertex, int toVertex);

    /// @brief Function will return first neighbour from given vertex neighbors collection (linked list)
    /// @param vertex vertex to get neighbors of
    /// @return head of linked list if success, NULL otherwise
    Connection* GetHeadOfVertexConnections(int vertex);

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
