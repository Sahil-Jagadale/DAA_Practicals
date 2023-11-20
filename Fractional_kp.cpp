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

int partition(Item arr[], int low,int high){
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

void quicksort(Item arr[],int low,int high){
    if(low < high){
        int pi = partition(arr,low,high);
        quicksort(arr,low,pi-1);
        quicksort(arr,pi+1,high);
    }
}

void fk(Item arr[], int n, double capacity){
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
        else{
            double remw = capacity-curw;
            curw+=remw;
            curp+=(arr[i].profit/arr[i].weight)*remw;
            if(remw != 0){
                cout<<"\nItem with weight "<<arr[i].weight<<" slected partially | Weight Ratio: "<<(capacity-arr[i].weight)/arr[i].weight<<"\n Profit by slecting item is "<<(arr[i].profit/arr[i].weight)*remw<<"\nRemaining weight = "<<capacity-curw<<endl;
            }
            break;
        }
    }
    cout<<"Maximum profit: "<<curp<<endl;
    cout<<"Remainig weight: "<<capacity-curw<<endl;
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
        cout<<arr[i].weight<<" ";
    }
    cout<<endl;

    fk(arr.data(),n,capacity);

}
