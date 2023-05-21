#include "Headers/binary_heap.h"

#pragma region CTOR_DTOR

BinaryHeap::BinaryHeap(int maxSize)
{
    heap = new HeapNode*[maxSize];
    BinaryHeap::maxSize = maxSize;
    BinaryHeap::size = 0;
}

BinaryHeap::~BinaryHeap()
{ 
    BinaryHeap::RemoveAll();
}
#pragma endregion CTOR_DTOR

#pragma region PRIVATE

int BinaryHeap::GetIndexOfLeftChild(int parentIndex)
{
    int index = 2 * parentIndex + 1;
    return (index < BinaryHeap::size)? index : -1;
}

int BinaryHeap::GetIndexOfRightChild(int parentIndex)
{
    int index = 2 * parentIndex + 2;
    return (index < BinaryHeap::size)? index : -1;
}

int BinaryHeap::GetIndexOfParent(int current)
{
    int index = (current - 1)/2;
    return (current > 0)? index : -1;
}

void BinaryHeap::GetTreeAsString(std::string prefix, int index, bool isRight, std::string& con)
{    
    if(index >= 0 && index < BinaryHeap::size)
    {
        con += prefix;

        con += isRight ? "|--:" : "*--:" ;

        // print the value of the node
        con += std::to_string(BinaryHeap::heap[index]->key);
        con += "("+std::to_string(BinaryHeap::heap[index]->heapIndex) + ")\n";

        // enter the next tree level - left and right branch
        BinaryHeap::GetTreeAsString( prefix + (isRight ? "|  " : "   "), GetIndexOfRightChild(index), true, con);
        BinaryHeap::GetTreeAsString( prefix + (isRight ? "|  " : "   "), GetIndexOfLeftChild(index), false, con);
    }
}

void BinaryHeap::FixUp(int index)
{
    int toAddParent = GetIndexOfParent(index);
    while (toAddParent >= 0 && BinaryHeap::heap[toAddParent]->key > BinaryHeap::heap[index]->key)
    {
        BinaryHeap::heap[toAddParent]->heapIndex = index;
        BinaryHeap::heap[index]->heapIndex = toAddParent;

        HeapNode* temp = BinaryHeap::heap[toAddParent];
        BinaryHeap::heap[toAddParent] = BinaryHeap::heap[index];
        BinaryHeap::heap[index] = temp;

        index = toAddParent;
        toAddParent = GetIndexOfParent(index);
    }
}

void BinaryHeap::FixDown(int index)
{
    while (index >= 0)
    {
        int swapTo = index;
        int left = GetIndexOfLeftChild(index);
        int right = GetIndexOfRightChild(index);

        if(left >=0 && BinaryHeap::heap[swapTo]->key > BinaryHeap::heap[left]->key)
            swapTo = left;
        
        if(right >=0 && BinaryHeap::heap[swapTo]->key > BinaryHeap::heap[right]->key)
            swapTo = right;
        
        if(swapTo == index)
            break;

        BinaryHeap::heap[swapTo]->heapIndex = index;
        BinaryHeap::heap[index]->heapIndex = swapTo;

        HeapNode* temp = BinaryHeap::heap[index];
        BinaryHeap::heap[index] = BinaryHeap::heap[swapTo];
        BinaryHeap::heap[swapTo] = temp;

        index = swapTo;
    }
}


#pragma endregion PRIVATE

#pragma region PUBLIC

HeapNode* BinaryHeap::Push(int key, int* data)
{
    if(BinaryHeap::size == BinaryHeap::maxSize)
    {
        return NULL;
    }
    BinaryHeap::size ++;

    int toAddIndex = BinaryHeap::size -1;

    HeapNode* node = new HeapNode(key, data);
    node->heapIndex = toAddIndex;
    BinaryHeap::heap[toAddIndex] = node;

    BinaryHeap::FixUp(toAddIndex);
    return node;
}

HeapNode* BinaryHeap::PopHead()
{
    if(BinaryHeap::size < 1)
    {
        return NULL;
    }
    if(BinaryHeap::size == 1)
    {
        BinaryHeap::size--;
        return BinaryHeap::heap[0];
    }    

    HeapNode* node = BinaryHeap::heap[0];
    BinaryHeap::heap[0] = BinaryHeap::heap[BinaryHeap::size -1];
    BinaryHeap::heap[0]->heapIndex = 0;
    BinaryHeap::size--;

    FixDown(0);

    return node;
}

void BinaryHeap::RemoveAll()
{
    if(BinaryHeap::size == 0)
        return;

    for (int i = 0; i < BinaryHeap::size; i++)
    {
        if(BinaryHeap::heap[i] != NULL)
        {
            delete BinaryHeap::heap[i];
        }
    }
    
    delete[] BinaryHeap::heap;
    BinaryHeap::heap = NULL;
    BinaryHeap::size = 0;
}

int BinaryHeap::GetSize()
{
    return BinaryHeap::size;
}

void BinaryHeap::EditKey(HeapNode* node, int newKey)
{
    node->key = newKey;
    BinaryHeap::FixUp(node->heapIndex);
}


std::string BinaryHeap::ToString()
{
    std::string res = "";
    BinaryHeap::GetTreeAsString("",0,false, res);
    return (res=="")? "NONE\n" : res + "\n";
}
#pragma endregion PUBLIC