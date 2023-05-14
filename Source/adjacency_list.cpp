#include "Headers/adjacency_list.h"

#pragma region CTOR / DTOR
AdjacencyList::AdjacencyList()
{
    AdjacencyList::Init();
}

AdjacencyList::AdjacencyList(std::string filePath, bool isTwoSided)
{
    AdjacencyList::Init();
    AdjacencyList::LoadDataFromFile(filePath, isTwoSided);
}

AdjacencyList::AdjacencyList(int vertexAmount)
{
    AdjacencyList::Init();
    AdjacencyList::SetVertexAmount(vertexAmount);
}

AdjacencyList::~AdjacencyList()
{
    AdjacencyList::RemoveAll();
}

#pragma endregion

#pragma region PRIVATE

void AdjacencyList::Init()
{
    AdjacencyList::size = 0;
    AdjacencyList::arr = NULL;
}

void AdjacencyList::RemoveAll()
{
    for (int i = 0; i < AdjacencyList::size; i++)
    {
        Connection* tmp = AdjacencyList::arr[i];
        while (tmp != NULL)
        {
            Connection* toRemove = tmp;
            tmp = tmp->nextConnection;
            delete toRemove;
        }
    }
    if(AdjacencyList::arr != NULL){
        delete AdjacencyList::arr;
        AdjacencyList::arr = NULL;
    }
}

#pragma endregion

#pragma region PUBLIC

bool AdjacencyList::LoadDataFromFile(std::string filePath, bool isTwoSided)
{
    std::ifstream file = std::ifstream(filePath);
    int edgeAmount, vertexAmount, beginVertex, endVertex;
    if(file.is_open() == false)
    {
        std::cout << "File error - OPEN" << std::endl;
        file.close();
        return false;
    }

    file >> edgeAmount;
    file >> vertexAmount;
    file >> beginVertex;
    file >> endVertex;
    if (file.fail()){
        std::cout << "File error - error with first line" << std::endl;
        file.close();
        return false;
    }
    AdjacencyList::SetVertexAmount(vertexAmount);
    AdjacencyList::SetBeginAndEndVertex(beginVertex,endVertex);

    for (int i = 0; i < edgeAmount; i++)
    {
        int from, to, weight;
        file >> from;
        file >> to;
        file >> weight;
        if (file.fail())
        {
            std::cout << "File error - READ DATA" << std::endl;
            file.close();
            return false;
        }
        else
        {
            AdjacencyList::SetConnection(from,to,weight);
            if(isTwoSided)
            {
                AdjacencyList::SetConnection(to,from,weight);
            }
        }
    }
    file.close();
    return true;
}

void AdjacencyList::SetVertexAmount(int amount)
{
    if(amount < 0)
    {
        return;
    }

    if(AdjacencyList::size > 0)
        AdjacencyList::RemoveAll();

    AdjacencyList::arr = new Connection*[amount];
    AdjacencyList::size = amount;
    for (int i = 0; i < amount; i++)
    {
        AdjacencyList::arr[i] = NULL;
    }   
}

bool AdjacencyList::SetConnection(int fromVertex, int toVertex, int weight, bool isTwoSided)
{
    if(fromVertex >= AdjacencyList::size || toVertex >= AdjacencyList::size  || fromVertex < 0 || toVertex < 0)
    {
        return false;
    }

    Connection* con = AdjacencyList::FindConnection(fromVertex, toVertex);
    if(con != NULL)
    {
        con->weight = weight;
    }
    else
    {
        Connection* newConnection = new Connection(toVertex, weight);
        newConnection->nextConnection = AdjacencyList::arr[fromVertex];
        AdjacencyList::arr[fromVertex] = newConnection;
    }

    if(isTwoSided == false)
    {
        return true;
    }

    con = AdjacencyList::FindConnection(toVertex, fromVertex);
    if(con != NULL)
    {
        con->weight = weight;
    }
    else
    {
        Connection* newConnection = new Connection(fromVertex, weight);
        newConnection->nextConnection = AdjacencyList::arr[toVertex];
        AdjacencyList::arr[toVertex] = newConnection;
    }

    return true;
}

Connection* AdjacencyList::FindConnection(int fromVertex, int toVertex)
{
    if(fromVertex >= AdjacencyList::size || toVertex >= AdjacencyList::size  || fromVertex < 0 || toVertex < 0)
    {
        return NULL;
    }
    Connection* next = AdjacencyList::arr[fromVertex];
    while (next != NULL)
    {
        if(next->vertex == toVertex)
        {
            return next;
        }
        next = next->nextConnection;
    }
    return NULL;
}

Connection* AdjacencyList::GetHeadOfVertexConnections(int vertex)
{
    if(vertex >= AdjacencyList::size || vertex < 0)
    {
        return NULL;
    }

    return AdjacencyList::arr[vertex];
}

void AdjacencyList::SetBeginAndEndVertex(int beginVertex, int endVertex)
{
    if(beginVertex >= AdjacencyList::size || endVertex >= AdjacencyList::size  || beginVertex < 0 || endVertex < 0)
    {
        return;
    }
    AdjacencyList::beginVertex = beginVertex;
    AdjacencyList::endVertex = endVertex;
}

int AdjacencyList::GetEndVertex()
{
    return AdjacencyList::endVertex;
}

int AdjacencyList::GetBeginVertex()
{
    return AdjacencyList::beginVertex;
}

int AdjacencyList::GetVertexAmount()
{
    return AdjacencyList::size;
}

std::string AdjacencyList::ToString()
{
    if(AdjacencyList::size == 0)
    {
        return "EMPTY\n";
    }
    std::string res = "";
    for (int i = 0; i < AdjacencyList::size; i++)
    {
        res += std::to_string(i) + "= ";
        Connection* next = AdjacencyList::arr[i];
        while (next != NULL)
        {
            res +=  "v:" + std::to_string(next->vertex) + "|" + "w:" + std::to_string(next->weight);
            next = next->nextConnection;
            if(next != NULL)
            {
                res += ", ";
            }
        }
        res += "\n";
    }
    return res;
}

#pragma endregion