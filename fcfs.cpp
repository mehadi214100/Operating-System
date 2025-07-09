#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[8] = {98,183,37,122,14,124,65,67};
    int total = 0;
    int initialposition = 53;
    for(int i=0;i<8;i++){
        total = total + abs(arr[i]-initialposition);
        initialposition = arr[i];
    }
    cout<<total<<endl;

}
