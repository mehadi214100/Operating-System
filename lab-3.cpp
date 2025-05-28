#include<bits/stdc++.h>
using namespace std;

int FIFO(vector<int>pages,int frames){
    vector<int>memory;
    int faults = 0;
    for(int page:pages){
        if(find(memory.begin(),memory.end(),page)==memory.end()){
            faults++;
            if (memory.size() == frames)
                memory.erase(memory.begin());
            memory.push_back(page);
        }
    }
    return faults;
}
int LRU(vector<int> pages, int frames) {
    vector<int> memory;
    unordered_map<int, int> recent;
    int faults = 0;
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
    }
    return faults;
}

int Optimal(vector<int> pages, int frames){
    vector<int>memory;
    int faults = 0;
    for(int i=0;i<pages.size();i++){
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()){
            faults++;
            if(memory.size()==frames){
                int far = i+1,idx=-1;
                for(int j=0;j<memory.size();j++){
                    int k;
                    for(k=i+1;k<pages.size();k++){
                        if(pages[k]==memory[j])break;
                    }
                    if(k>far){
                        far = k;
                        idx = j;
                    }
                }
                if(idx==-1)memory.erase(memory.begin());
                else memory.erase(memory.begin() + idx);
            }
            memory.push_back(page);
        }
    }
    return faults;
}

int main(){
    vector<int>pages ={1,2,3,4,2,1,5,6,2,1,2,3,7,6,3,2,1,2,3,6};
    cout<<"\nFIFO Replacement:\n";
    cout<<"-----------------------\n";
    cout<<"Frame  No of Faults\n";
    for(int i=3;i<=7;i++){
        cout<<i<<"\t"<<FIFO(pages,i)<<endl;
    }
    cout<<endl;
    cout<<"\LRU Replacement:\n";
    cout<<"-----------------------\n";
    cout<<"Frame  No of Faults\n";
    for(int i=3;i<=7;i++){
        cout<<i<<"\t"<<LRU(pages,i)<<endl;
    }

    cout<<endl;
    cout<<"\Optimal Replacement:\n";
    cout<<"-----------------------\n";
    cout<<"Frame  No of Faults\n";
    for(int i=3;i<=7;i++){
        cout<<i<<"\t"<<Optimal(pages,i)<<endl;
    }

}

