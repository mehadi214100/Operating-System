#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, res;
    cout << "Enter no of Processes: ";
    cin >> n;
    cout << "Enter no of Resources: ";
    cin >> res;

    vector<int> allocation[n], max_need[n], available(res);

    // Input Allocation
    for(int i = 0; i < n; i++){
        cout << "Allocation for Process " << i << " : ";
        for(int j = 0; j < res; j++){
            int x;
            cin >> x;
            allocation[i].push_back(x);
        }
    }

    // Input Maximum Need
    for(int i = 0; i < n; i++){
        cout << "Maximum need for Process " << i << " : ";
        for(int j = 0; j < res; j++){
            int x;
            cin >> x;
            max_need[i].push_back(x);
        }
    }

    // Input Available
    cout << "Available Resources : ";
    for(int i = 0; i < res; i++){
        cin >> available[i];
    }

    // Calculate Need Matrix
    vector<int> currentNeed[n];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < res; j++){
            int x = max_need[i][j] - allocation[i][j];
            if(x < 0) x = 0;
            currentNeed[i].push_back(x);
        }
    }

    while (true) {
        // Safe State Check
        bool ok[n] = {false};
        int cunt = 0;
        vector<int> ans;
        vector<int> work = available;

        while (cunt < n) {
            bool found = false;
            for(int i = 0; i < n; i++){
                if (!ok[i]) {
                    bool canAllocate = true;
                    for(int j = 0; j < res; j++){
                        if(work[j] < currentNeed[i][j]){
                            canAllocate = false;
                            break;
                        }
                    }
                    if (canAllocate){
                        cunt++;
                        for(int j = 0; j < res; j++){
                            work[j] += allocation[i][j];
                        }
                        ans.push_back(i);
                        ok[i] = true;
                        found = true;
                    }
                }
            }
            if (!found) break;
        }

        if (cunt == n){
            cout << "System is in a safe state.\nSafe sequence is: ";
            for(int d : ans) cout << "P" << d << " ";
            cout << "\n";
        } else {
            cout << "System is in an unsafe state.\n";
            return 0;
        }

        // Request Feature
        char choice;
        cout << "\nDo you want to make a resource request? (y/n): ";
        cin >> choice;
        if (choice != 'y' && choice != 'Y') break;

        int pid;
        cout << "Enter process number (0 to " << n - 1 << "): ";
        cin >> pid;

        vector<int> request(res);
        cout << "Enter request for resources (size " << res << "): ";
        for(int i = 0; i < res; i++) cin >> request[i];

        bool canGrant = true;
        for(int i = 0; i < res; i++){
            if (request[i] > currentNeed[pid][i]){
                cout << "Error: Process has exceeded its maximum claim.\n";
                canGrant = false;
                break;
            }
            if (request[i] > available[i]){
                cout << "Error: Resources are not available currently.\n";
                canGrant = false;
                break;
            }
        }

        if (canGrant){
            // Pretend to allocate
            for(int i = 0; i < res; i++){
                available[i] -= request[i];
                allocation[pid][i] += request[i];
                currentNeed[pid][i] -= request[i];
            }

            // Check safety again
            bool ok2[n] = {false};
            int cunt2 = 0;
            vector<int> ans2;
            vector<int> work2 = available;

            while (cunt2 < n) {
                bool found = false;
                for(int i = 0; i < n; i++){
                    if (!ok2[i]) {
                        bool canAllocate = true;
                        for(int j = 0; j < res; j++){
                            if(work2[j] < currentNeed[i][j]){
                                canAllocate = false;
                                break;
                            }
                        }
                        if (canAllocate){
                            cunt2++;
                            for(int j = 0; j < res; j++){
                                work2[j] += allocation[i][j];
                            }
                            ans2.push_back(i);
                            ok2[i] = true;
                            found = true;
                        }
                    }
                }
                if (!found) break;
            }

            if (cunt2 == n){
                cout << "Request can be granted. System is still in a safe state.\n";
                cout << "New safe sequence: ";
                for(int d : ans2) cout << "P" << d << " ";
                cout << "\n";
            } else {
                cout << "Request cannot be granted. It would lead to an unsafe state.\n";
                // Rollback
                for(int i = 0; i < res; i++){
                    available[i] += request[i];
                    allocation[pid][i] -= request[i];
                    currentNeed[pid][i] += request[i];
                }
            }
        }
    }

    return 0;
}
