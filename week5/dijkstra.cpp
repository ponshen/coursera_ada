/*
Question description:
The file contains an adjacency list representation of an undirected weighted graph with 200 vertices labeled 1 to 200.
Each row consists of the node tuples that are adjacent to that particular vertex along with the length of that edge. 
For example, the 6th row has 6 as the first entry indicating that this row corresponds to the vertex labeled 6. 
The next entry of this row "141,8200" indicates that there is an edge between vertex 6 and vertex 141 that has length 8200. 
The rest of the pairs of this row indicate the other vertices adjacent to vertex 6 and the lengths of the corresponding edges.

Your task is to run Dijkstra's shortest-path algorithm on this graph, using 1 (the first vertex) as the source vertex, 
and to compute the shortest-path distances between 1 and every other vertex of the graph. 
If there is no path between a vertex v and vertex 1, we'll define the shortest-path distance between 1 and v to be 1000000. 
You should report the shortest-path distances to the following ten vertices, in order: 7,37,59,82,99,115,133,165,188,197.
*/

#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
typedef vector< vector< pair<int,int> > > vvpii;
const char* file_name = "dijkstraData.txt";
const int n = 200;
const int s = 1;
const int inf = 1000000;
const int query[10] = {7,37,59,82,99,115,133,165,188,197};

class min_heap{
public:
    min_heap();
    bool isempty();
    void insertion(pair<int,int>);
    pair<int,int> extract_min();
private:
    void bubble_up(int i);
    void bubble_down(int i);
    vector< pair<int,int> > heap;
};

min_heap::min_heap(){heap.clear();}
bool min_heap::isempty(){return heap.empty();}

void min_heap::insertion(pair<int,int> node){
    heap.push_back(node);
    bubble_up(heap.size() - 1);
}

pair<int,int> min_heap::extract_min(){
    pair<int,int> top = heap[0];
    swap(heap[0], heap[ heap.size()-1 ]);
    heap.erase(heap.end()-1);
    bubble_down(0);
    return top;
}

void min_heap::bubble_up(int i){
    int prt = (i-1)/2;
    while(i != 0 && heap[i].second < heap[prt].second){
        swap(heap[i],heap[prt]);
        i = prt;
        prt = (i-1)/2;
    }
}

void min_heap::bubble_down(int i){
    unsigned left = 2*i+1, right = 2*i+2, smaller = 0;
    while( right < heap.size() && (heap[i].second > heap[left].second || heap[i].second > heap[right].second) ){
        if(heap[left].second < heap[right].second)
            smaller = left;
        else
            smaller = right;
        swap(heap[i],heap[smaller]);
        i = smaller;
        left = 2*i+1, right = 2*i+2;
    }
    if( left < heap.size() && heap[i].second > heap[left].second)
        swap(heap[i], heap[left]);
}

void output(const vector<int>& spl){
    /*print the query shortest path lengths*/
    int qn = sizeof(query)/sizeof(int);
    cout<<"Followings are shortest path lengths: "<<endl;
    for(int qi = 0; qi < qn; ++qi)
        cout<<"From vertex "<<s<<" to vertex "<<query[qi]<<": "<<spl[ query[qi]-1 ]<<endl;
}

void dijkstra(const vvpii& vList){
    int source = s - 1;
    /*initialization*/
    vector<int> spl(n, inf);
    vector<bool> visited(n, false);
    min_heap Q;
    spl[source] = 0;
    Q.insertion( pair<int,int>(source, spl[source]) );
    /*main loop: find shortest paths*/
    int u,v,weight;
    while(!Q.isempty()){
        u = Q.extract_min().first;
        if(!visited[u]){
            visited[u] = true;
            for(unsigned j = 0; j < vList[u].size(); ++j){
                v = vList[u][j].first;
                weight = vList[u][j].second;
                if(spl[u] + weight < spl[v]){
                    spl[v] = spl[u] + weight;
                    Q.insertion( pair<int,int>(v,spl[v]) );
                }
            }
        }
    }
    output(spl);
}

int main(){
    /*read graph from input file*/
    ifstream inFile(file_name, ios::in);
    string read_str;
    vvpii vList(n);
    int u = 0,v = 0,cost = 0;
    char comma;
    /*read data and construct graph line by line*/
    cout<<"Reading the input file..."<<endl;
    while( getline(inFile, read_str) ){
        istringstream iss(read_str);
        iss>>u;
        while( iss.good() ){
            iss>> v >> comma >> cost;
            vList[u-1].push_back( pair<int,int>(v-1,cost) );
        }
    }
    cout<<"Computing shortest paths from source vertex "<<s<<"..."<<endl;
    dijkstra(vList);
    return 0;
}

