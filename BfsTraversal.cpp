#include<iostream>
#include<unordered_map>
#include<list>
#include<vector>
#include<queue>
using namespace std;
class graph{
    public:
        unordered_map< int , list< int > > adj;
        void addEdges(int edge1, int edge2, int direction){
            adj[edge1].push_back(edge2);
            if(direction == 0){         // if graph is undirected
                adj[edge2].push_back(edge1);
            }
        }
    void bfsTraversal( int node, unordered_map< int , bool > &visited, vector< int > &ans ){
        
        queue< int > q;
        q.push(node);
        visited[node] = true;

        while(!q.empty()){
            int frontNode = q.front();
            q.pop();
            ans.push_back(frontNode);

            for(auto i : adj[frontNode]){
                if(!visited[i]){
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
};

int main(){

    int n;
    cout<< "Enter the nodes: ";
    cin>> n;

    int m;
    cout<< "Enter the No of edges:";
    cin>> m;

    graph g;
    cout<< "Enter the edges:\n";
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        g.addEdges(u, v, 0);
    }
    unordered_map< int , bool > visited;
    vector< int > ans;

    for(int i = 0; i < n; i++){
        if(!visited[i]){
            g.bfsTraversal( i, visited, ans);
        }
    }
    for(auto i: ans){
        cout<< i << " ";
    }
    return 0;
}