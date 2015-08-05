#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

/*
Question description:
The file "kargerMinCut.txt" contains the adjacency list representation of a simple undirected graph. There are 200 vertices labeled 1 to 200. 
The first column in the file represents the vertex label, and the particular row (other entries except the first column) 
tells all the vertices that the vertex is adjacent to. So for example, the 6th row looks like : "6	155	56	52	120	......". 
This just means that the vertex with label 6 is adjacent to (i.e., shares an edge with) the vertices with labels 155,56,52,120,......,etc

Your task is to code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph to compute the min cut.
*/

using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int n = 200;

class disjoint_set{
public:
    disjoint_set(int n);
    int sfind(int u);
    void smerge(int u, int v);
private:
    vector< pair<int,int> > ds;
};

disjoint_set::disjoint_set(int n){
    ds.resize(n);
    for(int i = 0; i != n; ++i){
        ds[i].first = i;    //parent
        ds[i].second = 0;   //rank
    }
}

int disjoint_set::sfind(int u){
    if(ds[u].first != u)
        ds[u].first = sfind(ds[u].first);
    return ds[u].first;
}

void disjoint_set::smerge(int u, int v){
    int uRoot = sfind(u);
    int vRoot = sfind(v);
    if(uRoot == vRoot){
      cout<<"already in the same set."<<endl;
      return;
    }
    if(ds[uRoot].second > ds[vRoot].second)
        ds[vRoot].first = uRoot;
    else if (ds[uRoot].second < ds[vRoot].second)
        ds[uRoot].first = vRoot;
    else{
        ds[uRoot].first = vRoot;
        ds[vRoot].second = ds[vRoot].second + 1;
    }
}
/*Fisher-Yates shuffle of eList*/
void shuffle(vector< pair<int,int> > &eList){
    int m = eList.size();
    for(int k = m-1; k > 0; --k){
        int r = rand()% (k+1);
        swap(eList[r], eList[k]);
    }
}

int mincut(const vector< pair<int,int> > &eList){
    int m = eList.size();
    /*iterate random-shuffled eList.*/
    /*for edge(u,v), if u and v have not been merged, merge u and v.*/
    /*terminate when only two vertices remain*/
    disjoint_set S(m);
    int ncnt = n;
    vector< pair<int,int> >::const_iterator eit;
    for(eit = eList.begin(); eit != eList.end(); ++eit){
        if(ncnt <= 2) break;
        int u = eit->first, v = eit->second;
        if( S.sfind(u) != S.sfind(v) ){
            S.smerge(u,v);
            --ncnt;
        }
    }
    /*count # of edges crossing the cut*/
    /*for edge(u,v), if u and v are not merged, (u,v) is a crossing edge*/
    int ecnt = 0;
    for(eit = eList.begin(); eit != eList.end(); ++eit){
        int u = eit->first, v = eit->second;
        if(S.sfind(u) != S.sfind(v))
            ++ecnt;
    }
    return ecnt;
}

int rMinCut(){
    srand(time(0));
    cout<<"Loading input file \"kargerMinCut.txt\"...."<<endl;
    ifstream inFile ("kargerMinCut.txt", ios::in);
    vvi vList;
    vector<pair<int, int> > eList;
    string line;
    /*read input text*/
    while( getline(inFile, line) ){
        istringstream row(line);
        vList.push_back(vi( istream_iterator<int>(row), istream_iterator<int>() ));
    }
    /*construct edge adjacency list*/
    cout<<"Constructing adjacency list of edges..."<<endl;
    for(vvi::const_iterator nit = vList.begin(); nit != vList.end(); ++nit){
        vi::const_iterator uit= nit->begin();
        for(vi::const_iterator vit = uit; vit != nit->end(); ++vit){
            if(*uit < *vit)
                eList.push_back( pair<int, int>(*uit, *vit) );
        }
    }
    
    /*run the cut-finding subroutine n^2logn times*/
    int trial = 10000;
    cout<<"Run Karger's randomized minimum cut algorithm with number of trials = "<<trial<<endl<<endl;
    int mc = n*n;
    for(int i = 0; i < trial; ++i){
        shuffle(eList);
        mc = min(mc, mincut(eList));
    }
    return mc;
}

int main(){
    int result = rMinCut();
    cout<<"The minimum cut found is: "<<result<<endl;
    return 0;
}
