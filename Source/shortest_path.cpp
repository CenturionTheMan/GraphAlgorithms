#include "Headers/shortest_path.h"

int* GSP::Dijkstra(AdjacencyMatrix& matrix)
{
    int vertexAmount = matrix.GetVertexAmount();
    int* prev = new int[vertexAmount];
    HeapNode** nodes = new HeapNode*[vertexAmount];
    BinaryHeap heap(vertexAmount);
    

    for (int i = 0; i < vertexAmount; i++)
    {
        int* data = new int[1];
        data[0] = i;
        prev[i] = -1;
        if(i != matrix.GetBeginVertex())
        {
            nodes[i] = heap.Push(GSP::COST_INFINITY, data);
        }
        else
        {
            nodes[i] = heap.Push(0, data);
        }
    }
    
    while (heap.GetSize() > 0)
    {
        HeapNode* node = heap.PopHead();

        for (int i = 0; i < vertexAmount; i++)
        {
            int weight = matrix.GetWeight(node->data[0], i);
            if(weight == matrix.WEIGHT_INFINITY)
                continue;
            
            if(weight < 0)
            {
                delete node;
                delete[] nodes;
                delete[] prev;
                return NULL;
            }

            int curWeight = nodes[i]->key;
            if(weight + node->key < curWeight)
            {
                heap.EditKey(nodes[i], weight + node->key);
                prev[i] = node->data[0];
            }
        }
    }
    delete[] nodes;

    return prev;
}

int* GSP::Dijkstra(AdjacencyList& list)
{
    int vertexAmount = list.GetVertexAmount();
    int* prev = new int[vertexAmount];
    HeapNode** nodes = new HeapNode*[vertexAmount];
    BinaryHeap heap(vertexAmount);
    

    for (int i = 0; i < vertexAmount; i++)
    {
        int* data = new int[1];
        data[0] = i;
        prev[i] = -1;
        if(i != list.GetBeginVertex())
        {
            nodes[i] = heap.Push(GSP::COST_INFINITY, data);
        }
        else
        {
            nodes[i] = heap.Push(0, data);
        }
    }
    
    while (heap.GetSize() > 0)
    {
        HeapNode* node = heap.PopHead();
        
        Connection* current = list.GetHeadOfVertexConnections(node->data[0]);

        while (current != NULL)
        {
            int curWeight = nodes[current->vertex]->key;

            if(current->weight < 0)
            {
                delete node;
                delete[] nodes;
                delete[] prev;
                return NULL;
            }

            if(current->weight + node->key < curWeight)
            {
                heap.EditKey(nodes[current->vertex], current->weight + node->key);
                prev[current->vertex] = node->data[0];
            }

            current = current->nextConnection;
        }
    }
    delete[] nodes;

    return prev;
}


int* GSP::BellmanFord(AdjacencyMatrix& matrix)
{
    int vertexAmount = matrix.GetVertexAmount();
    int* prev = new int[vertexAmount];
    int* costs = new int[vertexAmount];

    for (int i = 0; i < vertexAmount; i++)
    {
        prev[i] = -1;
        costs[i] = GSP::COST_INFINITY;
    }
    costs[matrix.GetBeginVertex()] = 0;
    
    for (int mainCounter = 0; mainCounter < vertexAmount; mainCounter++)
    {
        bool hasChanged = false;

        for (int cur = 0; cur < vertexAmount; cur++)
        {
            for (int neigh = 0; neigh < vertexAmount; neigh++)
            {
                int weight = matrix.GetWeight(cur, neigh);
                if(weight == matrix.WEIGHT_INFINITY || costs[cur] == GSP::COST_INFINITY)
                    continue;
                
                if(costs[neigh] > costs[cur] + weight)
                {
                    hasChanged = true;
                    int newCost = costs[cur] + weight;
                    costs[neigh] = newCost;
                    prev[neigh] = cur;
                }                
            }   
        }
        if(hasChanged == false)
        {
            delete[] costs;
            return prev;
        } 
    }
    
    delete[] costs;
    delete prev;
    return NULL;
}

int* GSP::BellmanFord(AdjacencyList& list)
{
    int vertexAmount = list.GetVertexAmount();
    int* prev = new int[vertexAmount];
    int* costs = new int[vertexAmount];

    for (int i = 0; i < vertexAmount; i++)
    {
        prev[i] = -1;
        costs[i] = GSP::COST_INFINITY;
    }
    costs[list.GetBeginVertex()] = 0;
    
    for (int mainCounter = 0; mainCounter < vertexAmount; mainCounter++)
    {
        bool hasChanged = false;

        for (int cur = 0; cur < vertexAmount; cur++)
        {
            for (Connection* neigh = list.GetHeadOfVertexConnections(cur); neigh != NULL; neigh = neigh->nextConnection)
            {
                int weight =neigh->weight;
                if(costs[cur] == GSP::COST_INFINITY)
                    continue;

                if(costs[neigh->vertex] > costs[cur] + weight)
                {
                    hasChanged = true;
                    int newCost = costs[cur] + weight;
                    costs[neigh->vertex] = newCost;
                    prev[neigh->vertex] = cur;
                }      
            }
        }
        if(hasChanged == false)
        {
            delete[] costs;
            return prev;
        } 
    }
    
    
    delete[] costs;
    delete prev;
    return NULL;
}


std::string GSP::ToString(AdjacencyMatrix& matrix, int* predecessorsArr)
{
    if(predecessorsArr == NULL)
    {
        return "Predecessors array is NULL!\n";
    }


    std::stringstream result;
    int prec = 2;

    result << "SHORTEST PATH:\n";

    result << "predecessors arr: [";
    for (int i = 0; i < matrix.GetVertexAmount(); i++)
    {
        std::string suf = (i == matrix.GetVertexAmount() - 1)? "]" : ", ";
        result << predecessorsArr[i] << suf;
    }
    result << "\n";

    result<< "End   Dist  Path\n"; 
    for (int dest = 0; dest < matrix.GetVertexAmount(); dest++)
    {
        if(dest == matrix.GetBeginVertex())
            continue;

        std::string path = "";
        int sumDist = 0;
        int currentIndex = dest;
        result << std::setw(3) << std::setfill(' ') << dest << " | ";
        while(predecessorsArr[currentIndex] >= 0)
        {

            std::stringstream temp;
            temp << std::setw(prec) << std::setfill('_') << predecessorsArr[currentIndex];
            path = temp.str() + " " + path;

            sumDist += matrix.GetWeight(predecessorsArr[currentIndex], currentIndex);

            currentIndex = predecessorsArr[currentIndex];
        }
        result << std::setw(3) << std::setfill(' ') <<sumDist << "  | ";
        result << path << std::setw(prec) << std::setfill('_') << dest << "\n";
    }
    return result.str();
}

std::string GSP::ToString(AdjacencyList& list, int* predecessorsArr)
{
    if(predecessorsArr == NULL)
    {
        return "Predecessors array is NULL!\n";
    }

    std::stringstream result;
    int prec = 2;

    result << "SHORTEST PATH:\n";

    result << "predecessors arr: [";
    for (int i = 0; i < list.GetVertexAmount(); i++)
    {
        std::string suf = (i == list.GetVertexAmount() - 1)? "]" : ", ";
        result << predecessorsArr[i] << suf;
    }
    result << "\n";


    result<< "End   Dist  Path\n"; 
    for (int dest = 0; dest < list.GetVertexAmount(); dest++)
    {
        if(dest == list.GetBeginVertex())
            continue;

        std::string path = "";
        int sumDist = 0;
        int currentIndex = dest;
        result << std::setw(3) << std::setfill(' ') << dest << " | ";
        while(predecessorsArr[currentIndex] >= 0)
        {

            std::stringstream temp;
            temp << std::setw(prec) << std::setfill('_') << predecessorsArr[currentIndex];
            path = temp.str() + " " + path;

            sumDist += list.FindConnection(predecessorsArr[currentIndex], currentIndex)->weight;

            currentIndex = predecessorsArr[currentIndex];
        }
        result << std::setw(3) << std::setfill(' ') <<sumDist << "  | ";
        result << path << std::setw(prec) << std::setfill('_') << dest << "\n";
    }
    return result.str();
}
