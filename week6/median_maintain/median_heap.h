#ifndef MEDIANHEAP_H
#define MEDIANHEAP_H

#include "heap.h"


class MedianHeap{
public:
    MedianHeap();
    bool IsEmpty();
    int Size();
    int Top();
    void Pop();
    void Insert(int);
private:
    Heap min_heap_;
    Heap max_heap_;
    void Balance();
};

#endif // MEDIANHEAP_H
