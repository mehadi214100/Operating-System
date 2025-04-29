
#include<bits/stdc++.h>
using namespace std;

bool isSafeState(int n, int res, vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> &available, vector<int> &safeSeq){
    vector<bool> finished(n, false);
    vector<int> work = available;
    safeSeq.clear();
    int count = 0;

    while(count < n){
        bool found = false;
        for(int i = 0; i < n; i++){
            if(!finished[i]){
                bool canAllocate = true;
                for(int j = 0; j < res; j++){
                    if(work[j] < need[i][j]){
                        canAllocate = false;
                        break;
                    }
                }
                if(canAllocate){
                    for(int j = 0; j < res; j++){
                        work[j] += allocation[i][j];
                    }
                    safeSeq.push_back(i);
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if(!found) break;
    }

    return (count == n);
}

int main(){
    int n, res;
    cout << "Enter no of Processes: ";
    cin >> n;
    cout << "Enter no of Resources: ";
    cin >> res;

    vector<vector<int>> allocation(n, vector<int>(res));
    vector<vector<int>> max_need(n, vector<int>(res));
    vector<vector<int>> need(n, vector<int>(res));
    vector<int> available(res);

    // Input Allocation
    for(int i = 0; i < n; i++){
        cout << "Allocation for Process " << i << " : ";
        for(int j = 0; j < res; j++){
            cin >> allocation[i][j];
        }
    }

    // Input Max Need
    for(int i = 0; i < n; i++){
        cout << "Maximum need for Process " << i << " : ";
        for(int j = 0; j < res; j++){
            cin >> max_need[i][j];
            need[i][j] = max_need[i][j] - allocation[i][j];
        }
    }

    // Input Available
    cout << "Available Resources : ";
    for(int i = 0; i < res; i++){
        cin >> available[i];
    }

    // Initial Safe State Check
    vector<int> safeSequence;
    if(isSafeState(n, res, allocation, need, available, safeSequence)){
        cout << "System is in a safe state.\nSafe sequence: ";
        for(int p : safeSequence) cout << "P" << p << " ";
        cout << "\n";
    } else {
        cout << "System is in an unsafe state.\n";
        return 0;
    }

    while(true){
        char choice;
        cout << "\nDo you want to make a resource request? (y/n): ";
        cin >> choice;
        if(choice != 'y' && choice != 'Y') break;

        int pid;
        cout << "Enter process number (0 to " << n-1 << "): ";
        cin >> pid;

        vector<int> request(res);
        cout << "Enter request for resources: ";
        for(int i = 0; i < res; i++) cin >> request[i];

        bool valid = true;
        for(int i = 0; i < res; i++){
            if(request[i] > need[pid][i]){
                cout << "Error: Request exceeds process maximum need.\n";
                valid = false;
                break;
            }
            if(request[i] > available[i]){
                cout << "Error: Not enough available resources.\n";
                valid = false;
                break;
            }
        }

        if(valid){
            // Temporarily allocate
            for(int i = 0; i < res; i++){
                available[i] -= request[i];
                allocation[pid][i] += request[i];
                need[pid][i] -= request[i];
            }

            if(isSafeState(n, res, allocation, need, available, safeSequence)){
                cout << "Request can be granted. System is still safe.\nNew Safe sequence: ";
                for(int p : safeSequence) cout << "P" << p << " ";
                cout << "\n";
            } else {
                cout << "Request cannot be granted. It leads to unsafe state. Rolling back.\n";
                for(int i = 0; i < res; i++){
                    available[i] += request[i];
                    allocation[pid][i] -= request[i];
                    need[pid][i] += request[i];
                }
            }
        }
    }

    return 0;
}
