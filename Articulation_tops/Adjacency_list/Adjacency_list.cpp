#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Rib {
    int start, finish;
};

int M, N, time = 1;
vector<vector<int>> tops;
vector<int> Num;
vector<int> Low;
Rib input;
set<int> output;

void dfs(int top, int parent) {
    Num[top] = time;
    Low[top] = Num[top];
    time++;
    int children = 0;
    for (auto ending : tops[top]) {
        if (Num[ending] == 0) {
            dfs(ending, top);
            Low[top] = min(Low[top], Low[ending]);
            if (Low[ending] == Num[top] && parent != -1) {
                output.insert(top+1);
            }
            ++children;
        } else {
            Low[top] = min(Low[top], Num[ending]);
        }
    }
    if (parent == -1 && children > 1) {
        output.insert(top+1);
    }
}

int main() {
    cin >> M >> N;
    tops.resize(M);
    Num.resize(M, 0);
    Low.resize(M, INT32_MAX);
    for (int i = 0; i < N; ++i) {
        cin >> input.start >> input.finish;
        input.start--;
        input.finish--;
        tops[input.start].push_back(input.finish);
        tops[input.finish].push_back(input.start);
    }
    for (int i = 0; i < M; ++i) {
        sort(tops[i].begin(), tops[i].end());
    }
    dfs(0, -1);
    cout << output.size() << endl;
    for (auto top : output) {
        cout << top << endl;
    }
    return 0;
}