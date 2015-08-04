#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int choosePivot(const vector<int> &A,const int low,const int high,const int qnum){
    if (qnum == 1)
        return low;
    if (qnum == 2)
        return high;

    int mid = (low + high)/2;
    int pivot = low;
    int l = A.at(low), m = A.at(mid), h = A.at(high);
    if ((m-l)*(m-h) < 0)
        pivot = mid;
    else if ((h-m)*(h-l) < 0)
        pivot = high;
    return pivot;
}

void swapEle(vector<int> &A, const int a, const int b){
    int temp = A.at(a);
    A.at(a) = A.at(b);
    A.at(b) = temp;
}

int countAndPartition(vector<int> &A, const int low, const int high,const int pivot, int& compCount){
    if (pivot != low)
        swapEle(A, pivot, low);
    /*now A[low] is the pivot*/
    int p = A.at(low);
    int i = low + 1;
    int j = low + 1;
    for (j = low+1; j != high + 1; ++j){
        if (A.at(j) < p){
            swapEle(A, i, j);
            ++i;
        }
    }
    int bound = i - 1;
    swapEle(A, low, bound);
    compCount = compCount + high - low;
    return bound;
}

void quickSort(vector<int> &A, const int low, const int high, const int qnum, int& compCount){
    if (low == high) return;
    int pivot = choosePivot(A, low, high, qnum);
    int bound = countAndPartition(A, low, high, pivot, compCount);
    if (bound != low)
        quickSort(A, low, bound-1, qnum, compCount);
    if (bound != high)
        quickSort(A, bound+1, high, qnum, compCount);
}

int main(){
    cout<<"Reading input array from\"inputText.txt\"..."<<endl;
    ifstream inText("inputText.txt", ios::in);
    const int length = 10000;
    vector<int> inputArray (length, 0);
    for (int i = 0; i < length; ++i)
        inText>>inputArray.at(i);

    vector<int> A = inputArray, B = inputArray, C = inputArray;
    int c1 = 0, c2 = 0, c3 = 0;
    cout<<"Computed the number of comparisons..."<<endl<<endl;
    quickSort(A, 0, length-1, 1, c1);
    quickSort(B, 0, length-1, 2, c2);
    quickSort(C, 0, length-1, 3, c3);
    cout<<"Case1: always use the first element as pivot"<<endl;
    cout<<"Number of comparisons: "<<c1<<endl<<endl;
    cout<<"Case2: always use the last element as pivot"<<endl;
    cout<<"Number of comparisons: "<<c2<<endl<<endl;
    cout<<"Case3: use the 'median-of-three' as pivot"<<endl;
    cout<<"Number of comparisons: "<<c3<<endl;
    return 0;
}
