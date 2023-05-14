#include "Headers/adjacency_matrix.h"

#pragma region CTOR/DTOR

AdjacencyMatrix::AdjacencyMatrix()
{
    AdjacencyMatrix::Init();
}

AdjacencyMatrix::AdjacencyMatrix(int vertexAmount)
{
    AdjacencyMatrix::Init();
    AdjacencyMatrix::SetVertexAmount(vertexAmount);
}

AdjacencyMatrix::AdjacencyMatrix(std::string filePath, bool isTwoSided)
{
    AdjacencyMatrix::Init();
    AdjacencyMatrix::LoadDataFromFile(filePath, isTwoSided);
}

AdjacencyMatrix::~AdjacencyMatrix()
{
   AdjacencyMatrix::RemoveAll();
}

#pragma endregion CTOR/DTOR


#pragma region PRIVATE

void AdjacencyMatrix::Init()
{
    AdjacencyMatrix::sizeVertex = 0;
    AdjacencyMatrix::arr = NULL;
}

void AdjacencyMatrix::RemoveAll()
{
    if(AdjacencyMatrix::sizeVertex > 0)
    {
        for (int i = 0; i < AdjacencyMatrix::sizeVertex; i++)
        {
            delete[] AdjacencyMatrix::arr[i];
        }
        delete[] AdjacencyMatrix::arr;
    }
    AdjacencyMatrix::sizeVertex = 0;
}

#pragma endregion


#pragma region PUBLIC AND GENERAL

bool AdjacencyMatrix::LoadDataFromFile(std::string filePath, bool isTwoSided)
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
    AdjacencyMatrix::SetVertexAmount(vertexAmount);
    AdjacencyMatrix::SetBeginAndEndVertex(beginVertex, endVertex);

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
            AdjacencyMatrix::SetConnection(from,to,weight);
            if(isTwoSided)
            {
                AdjacencyMatrix::SetConnection(to,from,weight);
            }
        }
    }
    file.close();
    return true;
}

void AdjacencyMatrix::SetVertexAmount(int amount)
{
    if(amount < 0)
    {
        return;
    }

    if(AdjacencyMatrix::sizeVertex > 0)
        AdjacencyMatrix::RemoveAll();

    AdjacencyMatrix::sizeVertex = amount;
    
    int** newArr = new int*[AdjacencyMatrix::sizeVertex];
    for (int i = 0; i < AdjacencyMatrix::sizeVertex; i++)
    {
        newArr[i] = new int[AdjacencyMatrix::sizeVertex];
    }

    for (int i = 0; i < amount; i++)
    {
        for(int j = 0; j < amount; j++)
        {
            newArr[i][j] = AdjacencyMatrix::WEIGHT_INFINITY;   
        }
    }

    AdjacencyMatrix::arr = newArr;
}

bool AdjacencyMatrix::SetConnection(int vertexFrom, int vertexTo, int weight, bool isTwoSided)
{
    if(vertexFrom >= AdjacencyMatrix::sizeVertex || vertexTo >= AdjacencyMatrix::sizeVertex)
    {
        return false;
    }

    AdjacencyMatrix::arr[vertexFrom][vertexTo] = weight;

    if(isTwoSided)
    {
        AdjacencyMatrix::arr[vertexTo][vertexFrom] = weight;
    }

    return true;
}

int AdjacencyMatrix::GetWeight(int fromVertex, int toVertex)
{
    if(fromVertex >= AdjacencyMatrix::sizeVertex || toVertex >= AdjacencyMatrix::sizeVertex || toVertex <0 || fromVertex <0)
    {
        throw std::out_of_range("One or both vertexes are out of range!");
    }
    return AdjacencyMatrix::arr[fromVertex][toVertex];
}

void AdjacencyMatrix::SetBeginAndEndVertex(int beginVertex, int endVertex)
{
    if(beginVertex >= AdjacencyMatrix::sizeVertex || endVertex >= AdjacencyMatrix::sizeVertex || beginVertex <0 || endVertex <0)
    {
        return;
    }
    AdjacencyMatrix::beginVertex = beginVertex;
    AdjacencyMatrix::endVertex = endVertex;
}

int AdjacencyMatrix::GetEndVertex()
{
    return AdjacencyMatrix::endVertex;
}

int AdjacencyMatrix::GetBeginVertex()
{
    return AdjacencyMatrix::beginVertex;
}


int AdjacencyMatrix::GetVertexAmount()
{   
    return AdjacencyMatrix::sizeVertex;
}

std::string AdjacencyMatrix::ToString()
{
    if(AdjacencyMatrix::sizeVertex == 0)
    {
        return "EMPTY\n";
    }

    int precision = 4;
    std::stringstream stream;
    for (int i = 0; i < precision + 2; i++)
    {
        stream << " ";
    }
    
    for (int i = 0; i < AdjacencyMatrix::sizeVertex; i++)
    {
        stream << "[" << std::setw(2) << std::setfill('.') << i << "]";
        if(i != AdjacencyMatrix::sizeVertex - 1)
        {
            stream << ", ";
        }
    }
    stream << "\n";
    
    for (int i = 0; i < AdjacencyMatrix::sizeVertex; i++)
    {
        stream << "[" << std::setw(2) << std::setfill('.') << i <<"]: ";
        for (int j = 0; j < AdjacencyMatrix::sizeVertex; j++)
        {
            if(AdjacencyMatrix::arr[i][j] == AdjacencyMatrix::WEIGHT_INFINITY)
            {
                stream << "infi";
            }
            else{
                stream << std::setw(precision) << std::setfill('_') << AdjacencyMatrix::arr[i][j];
            }
            if(j != AdjacencyMatrix::sizeVertex - 1)
            {
                stream << ", ";
            }
        }   
        stream << "\n";
    }

    return stream.str();
}

#pragma endregion PUBLIC

