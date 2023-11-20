#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
void print(const vector<int>& subset){
    cout<<"{ ";
    for(int val : subset){
        cout<<val<<" ";
    }
    cout<<" }"<<endl;
}

void generate_subset(vector<int>& arr,int target,vector<int>& subset,int index){
    if(target==0){
        print(subset);
        return;
    }
    for(int i=index;i<=arr.size();i++){
        if(target-arr[i]>=0){
            subset.push_back(arr[i]);
            generate_subset(arr,target-arr[i],subset,i+1);
            subset.pop_back();
        }
    }
}

void sumsubset(vector<int>& arr,int target){
    vector<int> subset;
    generate_subset(arr,target,subset,0);
}

int main(){
    int n;
    cout<<"Enter the size of the array:- ";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter the elements of the array:- ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    int target;
    cout<<"Enter the target sum:- ";
    cin>>target;

    cout<<"All the possible subset that has the target sum are:- "<<endl;
    sumsubset(arr,target);
}