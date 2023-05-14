#include "Headers/disjoint_sets.h"
DisjointSets::DisjointSets(int size)
{
    DisjointSets::size = size;
    DisjointSets::arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
}

DisjointSets::~DisjointSets()
{
    delete[] DisjointSets::arr;
}

int DisjointSets::Find(int index)
{
    if(index >= DisjointSets::size)
    {
        return -1;
    }

    return DisjointSets::arr[index];
}

bool DisjointSets::Union(int elem1, int elem2)
{
    int repElem1 = DisjointSets::Find(elem1);
    int repElem2 = DisjointSets::Find(elem2);

    if(repElem1 == -1 || repElem2 == -1)
    {
        return false;
    }

    if(repElem1 != repElem2)
    {
        for (int i = 0; i < DisjointSets::size; i++)
        {
            if(DisjointSets::Find(i) == repElem2)
            {
                DisjointSets::arr[i] = repElem1;
            }
        }
        return true;
    }
    return false;
}



