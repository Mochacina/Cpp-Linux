#include <bits/stdc++.h>

using namespace std;

int func2(int arr[], int N){
    int li[101] = {0,};
    for(int i=0; i<N; i++){
        int n = arr[i];
        if (li[100-n]) return true;
        li[n] = 1;
    }
    return 0;
}

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    
    int size;
    cout << "Input array size: ";
    cin >> size;
    int arr[size+1];
    for(int i=0;i<size;i++){
        std::cin >> arr[i];
    }
    for(int i=0;i<size;i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
    std::cout << "return: " << func2(arr, size) << "\n";
    return 0;
}