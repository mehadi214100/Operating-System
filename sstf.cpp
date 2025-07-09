#include<bits/stdc++.h>
using namespace std;

int SSTF(vector<int> requests, int head) {
    int total = 0;
    vector<bool> visited(requests.size(), false);

    for (int i = 0; i < requests.size(); i++) {
        int minDist = INT_MAX;
        int index = -1;
        for (int j = 0; j < requests.size(); j++) {
            if (!visited[j]) {
                int dist = abs(head - requests[j]);
                if (dist < minDist) {
                    minDist = dist;
                    index = j;
                }
            }
        }
        visited[index] = true;
        total += minDist;
        head = requests[index];
    }
    return total;
}


int main(){
    int head = 53;
    vector<int>request = {98,183,37,122,14,124,65,67};

    cout<<"Total Time :"<<SSTF(request,head);

}
