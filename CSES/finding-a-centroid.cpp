#include<bits/stdc++.h>
using namespace std;
vector<int> g[200007];
int dp[200007], n, a, b;
 
void dfs(int v, int e) {
    dp[v] = 1;
    for(const int& i : g[v]) {
        if(i == e) continue;
        dfs(i, v);
        dp[v] += dp[i];
    }
}
 
int get_centroid(int v, int e) {
    for(const int& i : g[v]) {
        if(i == e) continue;
        if(dp[i] * 2 > n)
            return get_centroid(i, v);
    }
    return v;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 1; i < n; ++i) {
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, -1);
    cout << get_centroid(1, -1);
}
