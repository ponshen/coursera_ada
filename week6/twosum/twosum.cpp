/*
Question description:
The goal of this problem is to implement a variant of the 2-SUM algorithm.
The file contains 1 million integers, both positive and negative (there might be some repetitions!).
This is your array of integers, with the ith row of the file specifying the ith entry of the array.

Your task is to compute the number of target values t in the interval [-10000,10000] (inclusive) 
such that there are distinct numbers x,y in the input file that satisfy x+y=t. 
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;
const char* input_file = "2sum_test1M.txt";
const unsigned input_size = 1000000;
const long long low = -10000, high = 10000, scale = 10000;
const long long width = high - low + 1;

void twosum(){
    cout<<"This program computes the number of values t in the interval [-10000,10000] satisfying x+y=t where x and y are in input array and distinct."<<endl;
    cout<<"Reading input array from file \""<<input_file<<"\"..."<<endl;
    unordered_multimap<long long,long long> table;
    vector<bool> found(width, false);
    long long integer = 0, key = 0;
    /*Read input file and insert the integers into hash table with key value = (integer/10000)*/
    ifstream ifs(input_file,ios::in);
    while( ifs.good() ){
        ifs>>integer;
        key = integer / scale;
        table.insert( pair<long long,long long>(key,integer) );
    }
    /*Target: x+y=t, x and y are in the input array and distinct, and t lies in [-10000,10000]*/
    /*If x and y satisfying the condition, key(x) and */
    cout<<"Counting two-sum's..."<<endl;
    unordered_multimap<long long,long long>::local_iterator itx, ity;
    long long x = 0, y = 0, k = 0, sum = 0;
    for(unsigned i = 0; i < table.bucket_count(); ++i){
        if( table.bucket_size(i) == 0 ) continue;
        k = table.begin(i)->first;
        for(int b = -2; b <= 1; ++b){
            int j = table.bucket(-k+b);
            for(ity = table.begin(j); ity != table.end(j); ++ity){
                for(itx = table.begin(i); itx != table.end(i); ++itx){
                    x = itx->second, y = ity->second;
                    sum = x+y;
                    if( sum >= low && sum <= high && x != y)
                        found[x+y-low] = true;
                }
            }
        }
    }
    int cnt = 0;
    for(int i = 0; i < width; ++i)
        if(found[i])   ++cnt;
    cout<<"There are "<<cnt<<" target value t found."<<endl;
}

int main(){
    twosum();
    return 0;
}
