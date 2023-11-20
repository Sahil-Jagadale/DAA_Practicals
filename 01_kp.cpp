#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Item {
    double weight;
    double profit;
};

bool compare(Item a, Item b){
    double r1 = a.profit/a.weight;
    double r2 = b.profit/b.weight;
    return r1>r2;
}

int partition(vector<Item>& arr, int low,int high){
    double pivot = arr[high].profit/arr[high].weight;
    int i= low-1;
    for(int j=low;j<high;j++){
        if(compare(arr[j],arr[high])){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[high]);
    return i+1;
}

void quicksort(vector<Item>& arr,int low,int high){
    if(low < high){
        int pi = partition(arr,low,high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);
    }
}

void greddy_01(vector<Item>& arr, int n, double capacity){
    quicksort(arr,0,n-1);
    cout<<"P/W:- ";
    for(int i=0;i<n;i++){
        cout<<arr[i].profit/arr[i].weight<<" ";
    }
    cout<<endl;
    cout<<endl;
    int curw = 0;
    int curp = 0;
    for(int i=0;i<n;i++){
        if(curw+arr[i].weight<=capacity){
            curw+=arr[i].weight;
            curp+=arr[i].profit;
            cout<<"\nItem with weight "<<arr[i].weight<<" added\n Profit by slecting item is "<<arr[i].profit<<"\nRemaining weight = "<<capacity-curw<<endl;
        }
    }
    cout<<"Maximum profit: "<<curp<<endl;
    cout<<"Remainig weight: "<<capacity-curw<<endl;
}

void print_table(const vector<vector<int>>& dp){
    for(const auto& row : dp){
        for(int val : row){
            cout<<val<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

int dp_01(vector<Item>& arr,double capacity){
    int n = arr.size();
    vector<vector<int>> dp(n+1, vector<int> (capacity+1,0));

    for(int i=1;i<=n;i++){
        for(int w=1;w<=capacity;w++){
            if(arr[i-1].weight<=w){
                dp[i][w] = max(static_cast<int> (arr[i-1].profit+dp[i-1][w - arr[i-1].weight]) , static_cast<int> (dp[i-1][w]));
            }
            else{
                dp[i][w]=dp[i-1][w];
            }
        }
        cout<<"Print Table:- "<<endl;
        print_table(dp);

        double remc = capacity;

        cout<<"Remaining capacity and Profit at ecah iteration"<<endl;

        for(int i=n;i>0;i--){
            if(dp[i-1][remc] != dp[i][remc]){
                cout<<"Item "<<i<<" selected. Remaining capacity is "<<remc - arr[i-1].weight<<endl;
                cout<<"Profit of selected item is "<<arr[i-1].profit<<endl;
                remc -= arr[i-1].weight;
            }
        }
        cout<<endl;
    }
    return dp[n][capacity];
}

int main(){
    int n;
    cout<<"Enter the numebr of items: ";
    cin>>n;
    cout<<endl;
    vector<Item> arr(n);
    int capacity;
    cout<<"Enter the capacity of the knapsack:- ";
    cin>>capacity;
    cout<<endl;
    cout<<"Enter the weights of all the items:- ";
    for(int i=0;i<n;i++){
        cin>>arr[i].weight;
    }
    cout<<"Enter the profits of all the items:- ";
    for(int i=0;i<n;i++){
        cin>>arr[i].profit;
    }
    cout<<"Weights:- ";
    for(int i=0;i<n;i++){
        cout<<arr[i].weight<<" ";
    }
    cout<<endl;
    cout<<"Profits:- ";
    for(int i=0;i<n;i++){
        cout<<arr[i].profit<<" ";
    }
    cout<<endl;

    //fk(arr.data(),n,capacity);
    int ch;
    cout<<"1. 0/1 Knapsack by greedy."<<endl;
    cout<<"2. 0/1 Knapsack by Dynamic programming."<<endl;
    cout<<"Enter your choice: ";
    cin>>ch;
    
    switch(ch){
        case 1:{
            greddy_01(arr,n,capacity);
            cout<<endl;
            break;
        }
        case 2:{
            int maxvalue = dp_01(arr,capacity);
            cout<<"Maximum Profit: "<<maxvalue<<endl;
            break;
        }
    }

}
