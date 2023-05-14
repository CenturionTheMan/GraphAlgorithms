#pragma once
#include <string>
#include <stdexcept>
#include <iostream>

/// @brief Node of heap
struct HeapNode
{
    int key;
    int heapIndex;
    int* data;

    HeapNode()
    {
        key = 0;
        heapIndex = -1;
        data = NULL;
    }
    HeapNode(int key, int* data)
    {
        this->key = key;
        this->data = data;
        heapIndex = -1;
    }

    ~HeapNode()
    {
        if(data != NULL)
        {
            delete[] data;
        }
    }
};


/// @brief Data structure of binary tree type
class BinaryHeap
{
private:
    HeapNode** heap;
    int size; //elements amount in heap
    int maxSize; //heap max size

    /// @brief Function will return index of left child of given parent
    /// @param parentIndex Parent index
    /// @return left child index or -1 if there is none
    int GetIndexOfLeftChild(int parentIndex);

    /// @brief Function will return index of right child of given parent
    /// @param parentIndex Parent index
    /// @return right child index or -1 if there is none
    int GetIndexOfRightChild(int parentIndex);

    /// @brief Function will return index of parent of given child
    /// @param current Child index
    /// @return parent index or -1 if there is none
    int GetIndexOfParent(int current);

    /// @brief Function will recursively call itself in order to create string representation of tree structure
    /// @param prefix Custom prefix to initialize each new element. Empty as default
    /// @param index Index of given element. Root index as default 
    /// @param isRight If given element is right child
    /// @param con final string 
    void GetTreeAsString(std::string prefix, int index, bool isRight, std::string& con);

    /// @brief Function will fix heap (going up)
    /// @param index index from which repairs begins
    void FixUp(int index);

    /// @brief Function will fix heap (going down)
    /// @param index index from which repairs begins
    void FixDown(int index);

public:
    /// @brief CTOR
    BinaryHeap(int maxSize);

    /// @brief DTOR, will free resources
    ~BinaryHeap();

    /// @brief Function will push new key-data into heap and repair it
    /// @param key key
    /// @param data data
    /// @return pushed node
    HeapNode* Push(int key, int* data);

    /// @brief Function will get node from root and repair heap
    /// @return node from root
    HeapNode* PopHead();

    /// @brief Function will remove all stack elements
    void RemoveAll();

    /// @brief 
    /// @return amount of elements in heap
    int GetSize();

    /// @brief Function will edit key of given node in heap and fix it
    /// @param node node to edit
    /// @param newKey new key to set
    void EditKey(HeapNode* node, int newKey);

    /// @brief 
    /// @return This data structure in string representation
    std::string ToString();
};

