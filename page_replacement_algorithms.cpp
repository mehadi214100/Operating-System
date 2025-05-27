
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Function to implement FIFO page replacement
void FIFO(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    cout << "\nFIFO Page Replacement:\n";
    for (int page : pages) {
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            faults++;
            if (memory.size() == frames)
                memory.erase(memory.begin());
            memory.push_back(page);
        }
        for (int m : memory) cout << m << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

// Function to implement LRU page replacement
void LRU(vector<int> pages, int frames) {
    vector<int> memory;
    unordered_map<int, int> recent;
    int faults = 0;

    cout << "\nLRU Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int lru = i, idx = -1;
                for (int j = 0; j < memory.size(); j++) {
                    if (recent[memory[j]] < lru) {
                        lru = recent[memory[j]];
                        idx = j;
                    }
                }
                memory.erase(memory.begin() + idx);
            }
            memory.push_back(page);
        }
        recent[page] = i;
        for (int m : memory) cout << m << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

// Function to implement Optimal page replacement
void Optimal(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    cout << "\nOptimal Page Replacement:\n";
    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int farthest = i + 1, idx = -1;
                for (int j = 0; j < memory.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == memory[j])
                            break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                if (idx == -1) memory.erase(memory.begin());
                else memory.erase(memory.begin() + idx);
            }
            memory.push_back(page);
        }
        for (int m : memory) cout << m << " ";
        cout << "\n";
    }
    cout << "Total Page Faults: " << faults << "\n";
}

int main() {
    int n, frames;
    cout << "Enter number of pages: ";
    cin >> n;
    vector<int> pages(n);
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> frames;

    FIFO(pages, frames);
    LRU(pages, frames);
    Optimal(pages, frames);

    return 0;
}
/*Input
12
7 0 1 2 0 3 0 4 2 3 0 3
3
*/
