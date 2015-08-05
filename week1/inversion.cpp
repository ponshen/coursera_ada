#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*
Question description:
The file "IntegerArray.txt" contains all of the 100,000 integers between 1 and 100,000 (inclusive) in some order, with no integer repeated.
Your task is to compute the number of inversions in the file given, where the ith row of the file indicates the i_th entry of an array.
*/

long long mergeAndCount(vector<int> &arr, vector<int> &temp, int low, int mid, int high){
    int indexL = low;       //index of left half of array
    int indexR = mid + 1;   //index of right half of array
    int indexT = low;       //index used for copying elements from and to temp array
    long long splitInv = 0; //count of split inversions

    while (indexL <= mid && indexR <= high){
        /*left > right, copy right one and count inversions*/
        if (arr.at(indexL) > arr.at(indexR)){
            temp.at(indexT) = arr.at(indexR);
            splitInv = splitInv + mid - indexL + 1;
            ++indexR, ++indexT;
        }
        else{    //left <= right: copy left box.
            temp.at(indexT) = arr.at(indexL);
            ++indexL, ++indexT;
        }
    }
    /*copy remaining*/
    while (indexL <= mid){ //right half exhausted first
        temp.at(indexT) = arr.at(indexL);
        ++indexL, ++indexT;
    }
    while (indexR <= high){//left half exhausted first
        temp.at(indexT) = arr.at(indexR);
        ++indexR, ++indexT;
    }
    /*copy the merged array back*/
    for (indexT = low; indexT <= high; ++indexT)
        arr.at(indexT) = temp.at(indexT);
    return splitInv;
}

long long sortAndCount(vector<int> &arr, vector<int> &temp, int low, int high){
    if (low == high) return 0;
    int mid = (low + high)/2;
    long long leftCount = sortAndCount(arr, temp, low, mid);
    long long rightCount = sortAndCount(arr, temp, mid+1, high);
    long long crossCount = mergeAndCount(arr, temp, low, mid, high);
    return leftCount + rightCount + crossCount;
}

int main(){
    vector <int> integers(100000, 0);
    vector <int> temp(100000, 0);
    cout<<"Reading input file \"IntegerArray.txt\"..."<<endl;
    ifstream inText("IntegerArray.txt", ios::in);
    for (int i = 0; i < 100000; ++i)
        inText>>integers.at(i);
    long long splitInv = sortAndCount(integers, temp, 0, 99999);
    cout<<"Number of  inversions: "<<splitInv<<endl;
    return 0;
}
