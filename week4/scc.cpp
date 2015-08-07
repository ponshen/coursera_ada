#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;
const char* input_name = "SCC.txt";

const int n = 875714, k = 5;
vector<int> order(n, 0);
vector<int> ftime(n, 0);
vector<int> leader(n, 0);
vector<bool> visited(n, false);
int s = 0,t = 0;

void dfs(const int u, const vector< vector<int> >& vList){
    visited[u] = true;
    leader[u] = s;
    if(vList[u].size() > 0){
        vector<int>::const_iterator it;
        for(it = vList[u].begin(); it != vList[u].end(); ++it){
            if(!visited[*it])
                dfs(*it, vList);
        }
    }
    ++t;
    ftime[u] = t;
}

void dfs_loop(const vector< vector<int> >& vList){
    int i = 0;
    for(i = 0; i < n; ++i)
        visited[i] = false;
    s = -1, t = -1;
    for(i = 0; i < n; ++i){
        if(!visited[ order[i] ]){
            s = order[i];
            dfs(s, vList);
        }
    }
}

void scc(){
    /*Construct the input graph and reversed graph.*/
    ifstream inFile(input_name, ios::in);
    cout<<"Reading the input file \""<<input_name<<"\"..."<<endl;;
    vector< vector<int> > vList(n);
    vector< vector<int> > vRevList(n);
    int u = 0, v = 0, i = 0;
    while(inFile.good()){
        inFile>>u>>v;
        vList[u-1].push_back(v-1);
        vRevList[v-1].push_back(u-1);
    }

    /*Run first DFS on reversed graph and determine the visit order of the second DFS.*/
    /*order[i] is the vertex number of i_th visited vertex*/
    /*Run second DFS on original graph and determine leaders of vertices.*/
    /*The leader of a vertex is the root of the dfs-tree to which that vertex belongs.*/
    cout<<"Run 2 times of DFSs, first on reversed graph and second on original graph."<<endl;
    for(i = 0; i < n; ++i){
        order[i] = i;
        leader[i] = i;
    }
    dfs_loop(vRevList);
    for(i = 0; i < n; ++i){
        order[ n-1 - ftime[i] ] = i;
    }
    dfs_loop(vList);

    /*count SCCs by seeing the leader of each vertex.*/
    /*vertices of the same leader belongs to the same scc.*/
    /*find top 5 large SCCs.*/
    cout<<"Counting the SCC sizes..."<<endl;
    vector<int> ldcount(n, 0);
    vector<int> scc_sizes(k, 0);
    for(i = 0; i < n; ++i)
        ++ldcount[ leader[i] ];

    int next = 0, pos = 0, temp = 0;
    for(i = 0; i < n; ++i){
        next = k-1;
        if(ldcount[i] > scc_sizes[next]){
            scc_sizes[next] = ldcount[i];
            pos = next;
            --next;
            while(next >= 0 && scc_sizes[pos] > scc_sizes[next]){
                temp = scc_sizes[pos];
                scc_sizes[pos] = scc_sizes[next];
                scc_sizes[next] = temp;
                pos = next;
                --next;
            }
        }
    }

    /*output 5 largest SCC sizes. Write 0 for the remaining terms if less than 5 SCCs.*/
    cout<<"Computing finished. The "<<k<<" largest SCC sizes are as follows:"<<endl;
    for(vector<int>::const_iterator it = scc_sizes.begin(); it != scc_sizes.end(); ++it)
        cout<< *it <<" ";
}

int main(){
    scc();
    return 0;
}
