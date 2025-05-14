
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process {
    int id, at, bt, priority, ct, tat, wt, rt, bt_remaining;
};

// FCFS Scheduling
void fcfs(vector<Process> p) {
    cout << "\n--- FCFS Scheduling ---\n";
    int n = p.size();
    sort(p.begin(), p.end(), [](Process a, Process b) { return a.at < b.at; });
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        p[i].wt = time - p[i].at;
        time += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    for (auto proc : p)
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.wt << "\t" << proc.tat << "\n";
}

// SJF Non-Preemptive
void sjf_non_preemptive(vector<Process> p) {
    cout << "\n--- SJF Non-Preemptive Scheduling ---\n";
    int n = p.size(), completed = 0, time = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].tat = p[idx].wt + p[idx].bt;
        done[idx] = true;
        completed++;
    }
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    for (auto proc : p)
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.wt << "\t" << proc.tat << "\n";
}

// SJF Preemptive (Shortest Remaining Time First)
void sjf_preemptive(vector<Process> p) {
    cout << "\n--- SJF Preemptive Scheduling ---\n";
    int n = p.size(), completed = 0, time = 0, min_idx;
    for (auto &proc : p) proc.bt_remaining = proc.bt;

    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt_remaining < min_bt && p[i].bt_remaining > 0) {
                min_bt = p[i].bt_remaining;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        p[idx].bt_remaining--;
        if (p[idx].bt_remaining == 0) {
            done[idx] = true;
            completed++;
            p[idx].tat = time + 1 - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
        time++;
    }
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    for (auto proc : p)
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.wt << "\t" << proc.tat << "\n";
}

// Round Robin
void round_robin(vector<Process> p, int tq) {
    cout << "\n--- Round Robin Scheduling ---\n";
    int n = p.size(), time = 0, completed = 0;
    vector<int> rem_bt(n);
    for (int i = 0; i < n; i++) rem_bt[i] = p[i].bt;
    vector<int> wt(n, 0), tat(n, 0);
    while (true) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = false;
                if (rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - p[i].bt;
                    rem_bt[i] = 0;
                    tat[i] = wt[i] + p[i].bt;
                }
            }
        }
        if (done) break;
    }
    cout << "PID\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << p[i].id << "\t" << p[i].bt << "\t" << wt[i] << "\t" << tat[i] << "\n";
}

// Priority Non-Preemptive
void priority_non_preemptive(vector<Process> p) {
    cout << "\n--- Priority Scheduling (Non-Preemptive) ---\n";
    int n = p.size(), time = 0, completed = 0;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, high_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].priority < high_priority) {
                high_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        p[idx].wt = time - p[idx].at;
        time += p[idx].bt;
        p[idx].tat = p[idx].wt + p[idx].bt;
        done[idx] = true;
        completed++;
    }
    cout << "PID\tAT\tBT\tPr\tWT\tTAT\n";
    for (auto proc : p)
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.priority << "\t" << proc.wt << "\t" << proc.tat << "\n";
}

// Priority Preemptive
void priority_preemptive(vector<Process> p) {
    cout << "\n--- Priority Scheduling (Preemptive) ---\n";
    int n = p.size(), time = 0, completed = 0;
    for (auto &proc : p) proc.bt_remaining = proc.bt;
    vector<bool> done(n, false);
    while (completed < n) {
        int idx = -1, high_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].priority < high_priority && p[i].bt_remaining > 0) {
                high_priority = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }

        p[idx].bt_remaining--;
        if (p[idx].bt_remaining == 0) {
            done[idx] = true;
            completed++;
            p[idx].tat = time + 1 - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
        time++;
    }
    cout << "PID\tAT\tBT\tPr\tWT\tTAT\n";
    for (auto proc : p)
        cout << proc.id << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.priority << "\t" << proc.wt << "\t" << proc.tat << "\n";
}

int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Arrival Time, Burst Time, Priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].priority;
    }
    cout << "Enter Time Quantum for Round Robin: ";
    cin >> tq;

    fcfs(p);
    sjf_non_preemptive(p);
    sjf_preemptive(p);
    round_robin(p, tq);
    priority_non_preemptive(p);
    priority_preemptive(p);

    return 0;
}
/*Input
4
0 8 2
1 4 1
2 9 3
3 5 2
2 //Time Quantum for Round Robin
*/
