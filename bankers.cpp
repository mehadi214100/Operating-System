#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,res;
    cout<<"Enter no of Process : ";
    cin>>n;
    cout<<"Enter no of Resources : ";
    cin>>res;

    vector<int>allocation[n],max_need[n],available(n);
    for(int i=0;i<n;i++){
        cout<<"Allocation for Process "<<i<<" : ";
        for(int j=0;j<res;j++){
            int x;
            cin>>x;
            allocation[i].push_back(x);
        }
    }

    for(int i=0;i<n;i++){
        cout<<"Maximum need for Process "<<i<<" : ";
        for(int j=0;j<res;j++){
            int x;
            cin>>x;
            max_need[i].push_back(x);
        }
    }
    cout<<"Available Resources : ";
    for(int i=0;i<res;i++){
        cin>>available[i];
    }
    vector<int>currentNeed[n];
    for(int i=0;i<n;i++){
        for(int j=0;j<res;j++){
            int x = max_need[i][j]-allocation[i][j];
            if(x<0) x = 0;
            currentNeed[i].push_back(x);
        }
    }
    bool ok[n] = {false};
    int cunt = 0,k=0;
    vector<int>ans;

    while(cunt<n){
        bool found = false;

        for(int i=0;i<n;i++){
            if(!ok[i]){
                bool canAllocate = true;
                for(int j=0;j<res;j++){
                    if(available[j]<currentNeed[i][j]){
                        canAllocate = false;
                        break;
                    }
                }
                if(canAllocate){
                    cunt++;
                    for(int j=0;j<res;j++){
                        available[j] += allocation[i][j];
                    }
                    ans.push_back(i);
                    ok[i] = true;
                    found = true;
                }
            }
        }
        if(!found){
            cout<<"System is in an unsafe state .\n";
            return 0;
        }
    }

    cout<<"System is in safe state.\nSafe sequence is : ";
    for(int d:ans) cout<<"P"<<d<<" ";

    return 0;
}
