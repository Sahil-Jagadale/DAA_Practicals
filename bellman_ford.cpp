#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

struct edge{
    int s,d,w;
};

int bf(int n,int e, int src,vector<edge>& edges, vector<int>& dist, vector<int>& parent){
    int s,w,d;
    int i,j;
    i=src;
    dist[i-1] = 0;
    parent[i-1] = -1;

    for(i = 1;i<n;i++){
        for(j=0;j<e;j++){
            s=edges[j].s;
            w=edges[j].w;
            d=edges[j].d;
            if(dist[s] != INT_MAX && dist[s]+w<dist[d]){
                dist[d]=dist[s]+w;
                parent[d]=s;
            }
        }
    }

    for(j=0;j<e;j++){
        s=edges[j].s;
        w=edges[j].w;
        d=edges[j].d;
        if(dist[s] != INT_MAX && dist[s]+w<dist[d]){
            return 0;
        }
    }
    return 1;
}

void print_path(int v, vector<int>& parent){
    if( v==-1 ) return;
    print_path(parent[v],parent);
    if(parent[v] != -1) cout<<"->";
    cout<<v+1;
}

int main(){
    int n,e;
    int s,w,d;
    cout<<"Enter the no. of vertices:- ";
    cin>>n;
    cout<<endl;
    cout<<"Enter the no. of edges:- ";
    cin>>e;
    cout<<endl;
    vector<edge> edges(e);
    vector<int> dist(n,INT_MAX);
    vector<int> parent(n,-1); 
    cout<<"Enter src, destination, weight for each edge: -"<<endl;
    for(int i=0;i<e;i++){
        cin>>s>>d>>edges[i].w;
        edges[i].s=s-1;
        edges[i].d=d-1;
    }
    cout<<endl;
    int src;
    cout<<"Enter the src vertex:- ";
    cin>>src;

    int result = bf(n,e,src,edges,dist,parent);

    if(result){
        cout<<"Vertex\tDistance\tPATH"<<endl;
        for(int i=0;i<n;i++){
            cout<<i+1<<"\t\t"<<dist[i]<<"\t\t";
            print_path(i,parent);
            cout<<endl;
        }
        cout<<endl;
    }
    else{
        cout<<"There presents an negative cycle in the given graph so bellman ford can't be performed!"<<endl;
    }
    return 0;
}
