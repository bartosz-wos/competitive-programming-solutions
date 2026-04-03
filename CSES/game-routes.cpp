#include<bits/stdc++.h>
using namespace std;
vector<int> g[100007];
vector<int> order;
constexpr int mod = 1e9 + 7;
int n, m, a, b, ind[100007];
long long dp[100007];
 
void toposort() {
    queue<int> Q;
    for(int i = 1; i <= n; ++i)
        if(!ind[i])
            Q.push(i);
    int u = 0;
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        order.push_back(u);
        for(const int& i : g[u])
            if(--ind[i] == 0)
                Q.push(i);
    }
}
 
void solve() {
    toposort();
    dp[n] = 1;
    for(int i = order.size() - 1; i >= 0; --i)
        for(const int& j : g[order[i]])
            dp[order[i]] = (dp[order[i]] + dp[j]) % mod;
    cout << dp[1];
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while(m--)
        cin >> a >> b, g[a].push_back(b), ++ind[b];
    solve();
}
