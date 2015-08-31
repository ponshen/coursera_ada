#ifndef HEAP_H
#define HEAP_H

#include<vector>
using std::vector;

class Heap{
public:
    Heap(bool);
    bool IsEmpty();
    int Size();
    void Insert(int);
    int Top();
    void Pop();
private:
    void BubbleUp(int);
    void BubbleDown(int);
    vector<int> container_;
    bool Compare(int,int);
    bool compare_type_;
};
#endif
