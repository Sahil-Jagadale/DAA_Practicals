#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

class Node{
    public:
        int vertex;
        int cost;
        int level;
        vector<vector<int>> matrix;
        vector<pair<int,int>> path;
};

Node* newNode(vector<vector<int>>& parent,vector<pair<int,int>>& path,int level,int par,int child){
    Node* temp = new Node;
    temp->path=path;
    if(level!=0){
        temp->path.push_back({par,child});
    }

    temp->matrix=parent;
    for(int k=0;k<parent.size() && level!=0; k++){
        temp->matrix[par][k]=INT_MAX;
        temp->matrix[k][child]=INT_MAX;
    }
    temp->matrix[child][0] = INT_MAX;

    temp->level = level;
    temp->vertex = child;

    return temp;
}


void ReduceRow(vector<vector<int>>& matrix, vector<int>& row) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            row[i] = min(matrix[i][j], row[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (row[i] != INT_MAX) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= row[i];
                    if (matrix[i][j] < 0) {
                        matrix[i][j] = INT_MAX;
                    }
                }
            }
        }
    }
}


void ReduceCol(vector<vector<int>>& matrix,vector<int>& col){
    int n = matrix.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(col[j]>matrix[i][j]){
                col[j]=matrix[i][j];
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(col[j]!=INT_MAX){
                if(matrix[i][j]!=INT_MAX){
                    matrix[i][j]-=col[j];
                }
            }
        }
    }
}

int calc_cost(vector<vector<int>>& matrix){
    int n=matrix.size();

    vector<int> row(n,INT_MAX), col(n,INT_MAX);
    ReduceRow(matrix,row);
    ReduceCol(matrix,col);
    int cost=0;
    for(int i=0;i<col.size();i++){
        if(row[i]!=INT_MAX) cost+=row[i];
        if(col[i]!=INT_MAX) cost+=col[i];
    }

    return cost;
}

class cmp{
    public:
        bool operator()(const Node* x,const Node* y){
            return x->cost > y->cost;
        }
};

void printpath(vector<pair<int,int>>& path){
    for(auto i : path){
        cout<<i.first+1<<"->"<<i.second+1<<endl;
    }
}

void TSP(vector<vector<int>>& adj){
    int n = adj.size();
    vector<pair<int,int>> path;
    Node* root = newNode(adj,path,0,-1,0);
    root->cost = calc_cost(root->matrix);

    priority_queue<Node*, vector<Node*>, cmp> pq;
    pq.push(root);

    while(!pq.empty()){
        Node* cur = pq.top();
        pq.pop();

        int ver = cur->vertex;
        if(cur->level == n-1){
            cur->path.push_back({ver,0});
            cout<<"Path:-"<<endl;
            printpath(cur->path);
            cout<<"Cost: "<<cur->cost<<endl;
            return;
        }

        for(int i=0;i<n;i++){
            if(cur->matrix[ver][i] != INT_MAX){
                Node* child = newNode(cur->matrix,cur->path,cur->level+1,ver,i);
                child->cost = cur->cost + cur->matrix[ver][i] + calc_cost(child->matrix);
                pq.push(child);
            }
        }
        delete(cur);
    }
}

int INF=INT_MAX;
int main(){
    vector<vector<int>> adj = {
        { INF, 20, 30, 10, 11 },
        { 15,  INF, 16,  4,  2 },
        { 3,   5,  INF, 2,  4 },
        { 19,   6,   18,   INF, 3 },
        { 16,   4,   7,   16, INF }
    };
    TSP(adj);

    return 0;
}