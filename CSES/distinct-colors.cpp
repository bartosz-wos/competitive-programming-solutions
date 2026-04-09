#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 7;
vector<int> adj[MAX_N];
set<int> colors[MAX_N];
int dp[MAX_N];
 
void dfs(int v, int e) {
    for (const int& i : adj[v]) {
        if (i == e) continue;
            dfs(i, v);
            if (colors[v].size() < colors[i].size()) {
                swap(colors[v], colors[i]);
            }
            for (const int& it : colors[i]) {
                colors[v].insert(it);
            }
    }
    dp[v] = colors[v].size();
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        colors[i].insert(a);
    }
    for (int i = 1; i < n; i++) {
        int a;
        int b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << (i < n ? " " : "\n");
    }
}
