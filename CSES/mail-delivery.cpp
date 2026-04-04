#include<bits/stdc++.h>
using namespace std;
int n, m;
set<int> g[100001];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].insert(b);
        g[b].insert(a);
    }
 
    for(int i = 1; i <= n; ++i)
        if(g[i].size() & 1) {
            cout << "IMPOSSIBLE";
            exit(0);
        }
 
    vector<int> res;
    stack<int> S;
    S.push(1);
 
    while(!S.empty()) {
        int u = S.top();
        if(g[u].empty()) {
            res.push_back(u);
            S.pop();
        }
        else {
            int v = *g[u].begin();
            g[u].erase(v);
            g[v].erase(u);
            S.push(v);
        }
    }
    if(res.size() != m + 1) {
        cout << "IMPOSSIBLE";
        exit(0);
    }
 
    for(const int& i : res)
        cout << i << ' ';
}
