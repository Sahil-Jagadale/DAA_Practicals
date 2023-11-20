#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print(int n,vector<int>& col){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(col[i]==j){
                cout<<i+1<<" ";
            }
            else{
                cout<<"O ";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

bool place(int queen,int c,vector<int>& col){
    int j=0;
    while(j<queen){
        if(col[j]==c || abs(col[j] - c)== abs(j - queen)){
            return false;
        }
        j++;
    }
    return true;
}

bool n_queen(int queen,int n,vector<int>& col){
    int fl=0;
    for(int i=0;i<n;i++){
        if(place(queen,i,col)){
            col[queen]=i;
            cout<<"Placing queen "<<queen+1<<endl;
            print(n,col);

            if( queen == n-1 ) return true;
            if(n_queen(queen+1,n,col)) return true;

            col[queen] = -1;
            cout<<"Backtracking queen "<<queen+1<<endl;
            print(n,col);
            fl=1;
        }
    }
    if(!fl){
        cout<<"Unable to place queen "<<queen+1<<endl;
    }
    return false;
}

int main(){
    int n;
    cout<<"Enter the size of chessboard:- ";
    cin>>n;
    if(n<=3){
        cout<<"Size of the chessboard is too small!";
        return 0;
    }
    vector<int> col(n);
    for(int i=0;i<n;i++){
        col[i]=-1;
    }
    n_queen(0,n,col);

    return 0;
}