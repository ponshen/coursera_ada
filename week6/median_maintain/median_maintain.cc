/*
Question description:
The goal of this problem is to implement the "Median Maintenance" algorithm.
The text file contains a list of the integers from 1 to 10000 in unsorted order; 
you should treat this as a stream of numbers, arriving one by one. 
Letting xi denote the ith number of the file, the kth median mk is defined as the median of the numbers x1,…,xk. 
(So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)
Your task is to compute (m1+m2+m3+⋯+m10000) (mod 10000)
*/
#include<iostream>
#include<vector>
#include<fstream>
#include "median_heap.h"
using namespace std;
const char* kFileName = "median.txt";
const int kInputSize = 10000, kModuler = 10000;

void ReadInput(vector<int>&);
void MedianMaintain(const vector<int>&);

void MedianMaintain(const vector<int>& input_array){
    cout<<"Computing sum of "<<kInputSize<<" medians (mod "<<kModuler<<")..."<<endl;
    MedianHeap median_heap;
    int sum = 0;
    for(int i = 0; i < kInputSize; ++i){
        median_heap.Insert(input_array[i]);
        sum = ( sum + median_heap.Top() ) % kModuler;
    }
    cout<<"The sum of "<<kInputSize<<" medians (mod "<<kModuler<<") is: "<<sum<<endl;
}

void ReadInput(vector<int>& input_array){
    cout<<"Reading input array of "<<kInputSize<<" integers..."<<endl;
    ifstream ifs(kFileName,ios::in);
    for(int i = 0; i < kInputSize; ++i)
        ifs>>input_array[i];
}

int main(){
    vector<int> input_array(kInputSize,0);
    ReadInput(input_array);
    MedianMaintain(input_array);
    return 0;
}