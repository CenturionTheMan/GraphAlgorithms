#include "Headers/disjoint_sets.h"
DisjointSets::DisjointSets(int size)
{
    DisjointSets::size = size;
    DisjointSets::sets = new SetElement*[size];
    for (int i = 0; i < size; i++)
    {
        sets[i] = new SetElement();
    }
}

DisjointSets::~DisjointSets()
{
    for (int i = 0; i < DisjointSets::size; i++)
    {
        delete sets[i];
    }
    delete[] sets;
}

SetElement* DisjointSets::Find(int index)
{
    if(index >= DisjointSets::size || index < 0)
    {
        return NULL;
    }

    SetElement* current = DisjointSets::sets[index];
    while (current->parent != current)
    {
        current = current->parent;
    }
    
    DisjointSets::sets[index]->parent = current;
    return current;
}

bool DisjointSets::Union(int elem1, int elem2)
{
    SetElement* repElem1 = DisjointSets::Find(elem1);
    SetElement* repElem2 = DisjointSets::Find(elem2);

    if(repElem1 == NULL || repElem2 == NULL)
    {
        return false;
    }

    if(repElem1 == repElem2)
    {
        return false;
    }

    if(repElem1->rank < repElem2->rank)
    {
        repElem1->parent = repElem2;
        repElem2->rank++;
    }
    else
    {
        repElem2->parent = repElem1;
        repElem1->rank++;
    }

    return true;
}



