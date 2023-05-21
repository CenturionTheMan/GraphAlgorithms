#include "Headers/ms_tree.h"

#pragma region KRUSKAL

AdjacencyMatrix MST::KruskalAlgorithm(AdjacencyMatrix& matrix)
{
    int vertexAmount = matrix.GetVertexAmount();

    AdjacencyMatrix result(vertexAmount);

    DisjointSets disjointSets(vertexAmount);
    BinaryHeap heap(vertexAmount * vertexAmount);
    for (int i = 0; i < vertexAmount; i++)
    {
        for (int j = i; j < vertexAmount; j++)
        {
            int weight = matrix.GetWeight(i, j);
            if(weight != matrix.WEIGHT_INFINITY)
            {
                int* data = new int[2];
                data[0] = i;
                data[1] = j;
                heap.Push(weight, data);
            }
        }
    }

    for (int i = 0; (i < vertexAmount - 1) && (heap.GetSize() > 0); )
    {
        int* data = heap.PopHead()->data;
        
        int v1 = data[0];
        int v2 = data[1];
        
        if(disjointSets.Union(v1, v2))
        {
            int weight = matrix.GetWeight(v1, v2);
            result.SetConnection(v1, v2, weight, true);
            i++;
        }
    }
    

    return result;
}

AdjacencyList MST::KruskalAlgorithm(AdjacencyList& list)
{
    int vertexAmount = list.GetVertexAmount();
    AdjacencyList result(vertexAmount);

    DisjointSets disjointSets(vertexAmount);
    BinaryHeap heap(vertexAmount * vertexAmount);

    for (int i = 0; i < vertexAmount; i++)
    {
        Connection* current = list.GetHeadOfVertexConnections(i);
        while (current != NULL)
        {
            int* data = new int[2];
            data[0] = i;
            data[1] = current->vertex;
            int weight = current->weight;
            heap.Push(weight, data);
            current = current->nextConnection;
        }
    }

    for (int i = 0; (i < 2*vertexAmount - 2) && (heap.GetSize() > 0); )
    {
        int* data = heap.PopHead()->data;
        int v1 = data[0];
        int v2 = data[1];
        
        if(disjointSets.Union(v1, v2))
        {
            int weight = list.FindConnection(v1, v2)->weight;
            result.SetConnection(v1, v2, weight, false);
            i++;
        }
    }
    return result;
}

#pragma endregion


#pragma region PRIMA

AdjacencyMatrix MST::PrimaAlgorithm(AdjacencyMatrix& matrix)
{
    int vertexAmount = matrix.GetVertexAmount();
    BinaryHeap heap(vertexAmount * vertexAmount);
    AdjacencyMatrix result = AdjacencyMatrix(vertexAmount);
    bool* visited = new bool[vertexAmount];
    for (int i = 0; i < vertexAmount; i++)
    {
        visited[i] = false;
    }

    visited[0] = true;
    int current = 0;
    for (int i = 0; i < vertexAmount - 1; i++)
    {
        for (int j = 0; j < vertexAmount; j++)
        {
            int weight = matrix.GetWeight(current,j);
            if(weight == matrix.WEIGHT_INFINITY)
            {
                continue;
            }
            int* toAdd = new int[2];
            toAdd[0] = current;
            toAdd[1] = j;
            heap.Push(weight,toAdd);
        }
        
        if(heap.GetSize() == 0)
            return result;

        while (heap.GetSize() > 0)
        {
            int* next = heap.PopHead()->data;
            int v1 = next[0];
            int v2 = next[1];
            if(visited[v2] == true)
            {
                continue;
            }
            visited[v2] = true;
            current = v2;
            result.SetConnection(v1, v2, matrix.GetWeight(v1, v2));
            result.SetConnection(v2, v1, matrix.GetWeight(v2, v1));
            break;
        }
    }
    delete[] visited;
    return result;
}

AdjacencyList MST::PrimaAlgorithm(AdjacencyList& list)
{
    int vertexAmount = list.GetVertexAmount();
    BinaryHeap heap(vertexAmount * vertexAmount);
    AdjacencyList result = AdjacencyList(vertexAmount);
    bool* visited = new bool[vertexAmount];
    for (int i = 0; i < vertexAmount; i++)
    {
        visited[i] = false;
    }

    visited[0] = true;
    int current = 0;
    for (int i = 0; i < vertexAmount - 1; i++)
    {
        Connection* currentAdj = list.GetHeadOfVertexConnections(current);
        while (currentAdj != NULL)
        {
            int* toAdd = new int[2];
            toAdd[0] = current;
            toAdd[1] = currentAdj->vertex;
            heap.Push(currentAdj->weight,toAdd);
            currentAdj = currentAdj->nextConnection;
        }
        
        if(heap.GetSize() == 0)
            return result;

        while (heap.GetSize() > 0)
        {
            int* next = heap.PopHead()->data;
            int v1 = next[0];
            int v2 = next[1];
            if(visited[v2] == true)
            {
                continue;
            }
            visited[v2] = true;
            current = v2;
            result.SetConnection(v1, v2, list.FindConnection(v1, v2)->weight);
            break;
        }
    }
    delete[] visited;
    return result;
}

#pragma endregion


std::string MST::ToString(AdjacencyMatrix& matrix)
{
    std::stringstream stream;
    stream << "Edge       Weight\n";
    int sumWeight = 0;

    for (int i = 0; i < matrix.GetVertexAmount(); i++)
    {
        for (int j = i; j < matrix.GetVertexAmount(); j++)
        {
            if(matrix.GetWeight(i,j) == matrix.WEIGHT_INFINITY)
            {
                continue;
            }
            int weight = matrix.GetWeight(i,j);
            sumWeight += weight;
            stream << "(" << std::setw(2) << std::setfill('.') << i << " - " << std::setw(2) << j << ")  " << std::setw(6) << weight <<"\n";
        }
    }
    stream <<"MST=" << sumWeight <<"\n";
    return stream.str();
}

std::string MST::ToString(AdjacencyList& list)
{
    std::stringstream stream;
    stream << "Edge       Weight\n";
    int sumWeight = 0;

    for (int i = 0; i < list.GetVertexAmount(); i++)
    {
        Connection* current = list.GetHeadOfVertexConnections(i);
        while (current != NULL)
        {
            int weight = current->weight;
            sumWeight += weight;
            stream << "(" << std::setw(2) << std::setfill('.') << i << " - " << std::setw(2) << current->vertex << ")  " << std::setw(6) << weight <<"\n";
            current = current->nextConnection;
        }
    }
    stream <<"MST=" << sumWeight <<"\n";
    return stream.str();
}

