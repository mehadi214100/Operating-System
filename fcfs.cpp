#include<bits/stdc++.h>
using namespace std;
int main(){
    cout<<"Enter no of process : ";
    int n;cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){

        cout<<"Burst time for P"<<i+1<<":";
        cin>>arr[i];
    }
    int waiting[n],tat[n];
    int sumWait = 0,sumTat = 0;
    for(int i=0;i<n;i++){
        if(i==0){
            waiting[i] = 0;
            tat[i] = arr[i];
            sumWait += waiting[i];
            sumTat += tat[i];
        }else{
            waiting[i] = waiting[i-1]+arr[i-1];
            tat[i] = waiting[i]+arr[i];
            sumWait += waiting[i];
            sumTat += tat[i];
        }
    }
    float avgW = sumWait*1.0/n;
    float avgTat = sumTat*1.0/n;
    cout<<"Process   Burst Time\tWaiting Time\tTurnaround Time"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    for(int i=0;i<n;i++){
        cout<<"P"<<i+1<<"\t\t"<<arr[i]<<"\t\t"<<waiting[i]<<"\t\t"<<tat[i]<<endl;
    }

    cout<<"Avg waiting time :"<<avgW<<endl;
    cout<<"Avg Turnaround time :"<<avgTat<<endl;
}
