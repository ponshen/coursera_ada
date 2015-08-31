#include "heap.h"
using std::swap;

Heap::Heap(bool type){
    container_.clear();
    compare_type_ = type;
}

bool Heap::Compare(int a, int b){return ( (compare_type_)? (a < b) : (a > b) );}

bool Heap::IsEmpty(){return container_.empty();}
int Heap::Size(){return container_.size();}

void Heap::Insert(int key){
    container_.push_back(key);
    BubbleUp(container_.size() - 1);
}

int Heap::Top(){return container_[0];}

void Heap::Pop(){
    swap(container_[0], container_[ container_.size()-1 ]);
    container_.erase(container_.end()-1);
    BubbleDown(0);
}

void Heap::BubbleUp(int i){
    int parent_index = (i-1)/2;
    while( i != 0 && Compare(container_[i],container_[parent_index]) ){
        swap(container_[i],container_[parent_index]);
        i = parent_index;
        parent_index = (i-1)/2;
    }
}

void Heap::BubbleDown(int i){
    unsigned left = 2*i+1, right = 2*i+2, smaller = 0;
    while( right < container_.size() &&
          ( Compare(container_[left],container_[i]) || Compare(container_[right],container_[i]) ) ){
        if( Compare(container_[left],container_[right]) )
            smaller = left;
        else
            smaller = right;
        swap(container_[i],container_[smaller]);
        i = smaller;
        left = 2*i+1, right = 2*i+2;
    }
    if( left < container_.size() && Compare(container_[left],container_[i]) )
        swap(container_[i], container_[left]);
}
