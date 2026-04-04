#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m, p, coins[100007];
ll group[100007], dp[100007];
vector<int> rgraph[100007];
 
struct SCC {
    vector<vector<int>> g, revg;
    vector<int> kos, comp, comps;
    bitset<100007> vis;
    void init() {
        g.resize(n+1);
        revg.resize(n+1);
        comp.resize(n+1, -1);
    }
    void addEdge() {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        revg[b].push_back(a);
    };
    void dfs1(int v) {
        vis[v] = 1;
        for(const int& i : g[v])
            if(!vis[i])
                dfs1(i);
        kos.push_back(v);
    }
    void dfs2(int v, int e) {
        comp[v] = e;
        for(const int& i : revg[v])
            if(comp[i] == -1)
                dfs2(i, e);
    }
    void kosaraju() {
        for(int i = 1; i <= n; ++i)
            if(!vis[i])
                dfs1(i);
        reverse(kos.begin(), kos.end());
        for(const int& i : kos)
            if(comp[i] == -1)
                dfs2(i, i), comps.push_back(i);
    }
};
 
ll DP(int i) {
    if(dp[i])
        return dp[i];
    dp[i] = group[i];
    for(const int& j : rgraph[i])
        dp[i] = max(dp[i], DP(j) + group[i]);
    return dp[i];
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    SCC graph;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> coins[i];
    graph.init();
    while(m--)
        graph.addEdge();
    graph.kosaraju();
    for(int i = 1; i <= n; ++i)
        group[graph.comp[i]] += coins[i];
    for(int i = 1; i <= n; ++i)
        for(const int& j : graph.g[i]) {
            if(graph.comp[i] == graph.comp[j]) continue;
            rgraph[graph.comp[j]].push_back(graph.comp[i]);
        }
    ll ans = 0;
    for(const int& i : graph.comps)
        ans = max(ans, DP(i));
    cout << ans;
}
