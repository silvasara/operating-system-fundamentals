#include <bits/stdc++.h>

using namespace std;

int main(){
    int N;
    cin >> N;
    vector<int> pages;

    while(N--){
        int p;
        cin >> p;
        pages.push_back(p);
    }

    vector<pair<int, int>> page_faults_frames;
    int frames;

    while(cin >> frames){
        list<int> table;
        int page_fault = 0; 
        bool fault = true; 
        int count = 0;

        for(auto i:pages){
            for(auto j:table){
                if(i==j){
                    fault = false;
                    break;
                }
            }

            if(fault){
                page_fault++;

                while(count<frames){
                    table.push_back(i);
                    count++;
                }

                table.pop_front();
                table.push_back(i);
            }
        
            fault = true;
        }

        page_faults_frames.push_back(make_pair(frames, page_fault));
    }

    for(auto i:page_faults_frames){
        cout << i.first << " " << i.second << endl;
    }

    sort(page_faults_frames.begin(), page_faults_frames.end());

    for(int i=1; i<page_faults_frames.size(); i++){
        if(page_faults_frames[i].second > page_faults_frames[i-1].second){
            cout << "Belady detectado\n";
            return 0;
        }
    }

    cout << "Sem anomalia\n";

    return 0;
}
