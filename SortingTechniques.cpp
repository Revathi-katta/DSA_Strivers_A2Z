#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//1.SELECTION SORT  TC: O(n^2), SC: O(1)
vector<int> selectionSort(vector<int> &arr){   
    for(int i=0; i<arr.size()-1; i++){             
        // Loop until second-to-last element since last element automatically gets sorted
        int minInd=i;                               //****
        for(int j=i; j<arr.size(); j++){         //can also Start from j=i+1
            if(arr[j]<arr[minInd]){minInd=j;}
        }
        swap(arr[i], arr[minInd]);
    }
    return arr;
}


//BUBBLESORT   TC:O(n^2), SC: O(1)
vector<int> bubbleSort(vector<int> &arr){
    for(int i=0; i<arr.size(); i++){ 
        bool isSwap=false;                              //****
        for(int j=1; j<arr.size()-i; j++){
            if(arr[j-1]>arr[j]){
                swap(arr[j-1], arr[j]);
                isSwap=true;}
        }
        if(isSwap==false){break;}       // Or if(!isSwap) break;
    }
    return arr;
}

//INSERTION SORT TC: O(n^2), SC: O(1)
vector<int> insertionSort(vector<int> &arr){
    for(int i=0; i<arr.size(); i++){ 
        int j=i;                              //****
        for(j; j>0; j--){
            if(arr[j-1]>arr[j]){
                swap(arr[j-1], arr[j]);
                }
        }  
    }
    return arr;   
}

//MERGE SORT TC: O(nlogn), SC: O(n)
void merge(vector<int>&arr, int low, int mid, int high){
    vector<int> temp;
    int l=low;
    int r=mid+1;
    while(l<=mid && r<=high){
        if(arr[l]<=arr[r]){
            temp.push_back(arr[l]);
            l++;
        }
        else if(arr[l]>arr[r]){
            temp.push_back(arr[r]);
            r++;
        }
    }
    while(l<=mid){
        temp.push_back(arr[l]);
        l++;
    }
    while(r<=high){
        temp.push_back(arr[r]);
        r++;
    }
    for(int i=low; i<=high; i++){  //**** i=low
        arr[i]=temp[i-low];
    }
}
void ms(vector<int>&arr, int low, int high){
    if(low==high)return;
    int mid=low+((high-low)/2);
    ms(arr, low, mid);
    ms(arr, mid+1, high);
    merge(arr, low, mid, high);
}
vector<int> mergeSort(vector<int>& arr) {
    int low=0;
    int high=arr.size()-1;
    ms(arr, low, high); // Call the helper function
    return arr;
}

//QUICK SORT TC: O(nlogn), SC: O(1)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];  // Choosing the pivot (first element)
    int l = low + 1;
    int r = high;

    while (l <= r) {
        // Move l to the right until arr[l] > pivot
        while (l <= high && arr[l] <= pivot) {
            l++;
        }
        // Move r to the left until arr[r] < pivot
        while (r >= low + 1 && arr[r] > pivot) {
            r--;
        }

        // If l < r, swap arr[l] and arr[r]
        if (l < r) {
            swap(arr[l], arr[r]);
        }
    }

    // Place the pivot at the correct position by swapping with arr[r]
    swap(arr[low], arr[r]);

    return r;  // Return the pivot index
}

void qs(vector<int>&arr, int low, int high){
    if(low<high){
        int pIndex=partition(arr, low, high);
        qs(arr, low, pIndex-1);   //***//pIndex-1
        qs(arr, pIndex+1, high);
    }
}
vector<int> quickSort(vector<int>& arr) {
    int low=0;
    int high=arr.size()-1;
    qs(arr, low, high); // Call the helper function
    return arr;
}

int main(){
    vector<int> arr={3,1,5,2,1,8};

    vector<int> ans1=selectionSort(arr);
    for(auto num : ans1){
        cout<<num<<" ";
    }
    cout<<"\n";

    vector<int> ans2=bubbleSort(arr);
    for(auto num : ans2){
        cout<<num<<" ";
    }
    cout<<"\n";

    vector<int> ans3=insertionSort(arr);
    for(auto num : ans3){
        cout<<num<<" ";
    }
    cout<<"\n";

    vector<int> ans4=mergeSort(arr);
    for(auto num : ans4){
        cout<<num<<" ";
    }
    cout<<"\n";

    vector<int> ans5=quickSort(arr);
    for(auto num : ans5){
        cout<<num<<" ";
    }
    cout<<"\n";
    return 0;
}

