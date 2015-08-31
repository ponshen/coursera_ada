#include "median_heap.h"

MedianHeap::MedianHeap()
:min_heap_(true), max_heap_(false){}

bool MedianHeap::IsEmpty(){return ( min_heap_.IsEmpty() && max_heap_.IsEmpty() );}
int MedianHeap::Size(){return ( min_heap_.Size() + max_heap_.Size() );}

int MedianHeap::Top(){
    return max_heap_.Top();
}

void MedianHeap::Pop(){
    max_heap_.Pop();
    Balance();
}

void MedianHeap::Insert(int key){
    if(IsEmpty()) max_heap_.Insert(key);
    else if(key < max_heap_.Top())  max_heap_.Insert(key);
    else  min_heap_.Insert(key);
    Balance();
}

void MedianHeap::Balance(){
    if( max_heap_.Size() < min_heap_.Size() ){
        max_heap_.Insert(min_heap_.Top());
        min_heap_.Pop();
    }
    else if( max_heap_.Size() - min_heap_.Size() > 1 ){
        min_heap_.Insert(max_heap_.Top());
        max_heap_.Pop();
    }
}
