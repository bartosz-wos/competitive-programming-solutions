#include<bits/stdc++.h>
#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
using namespace std;
int n, m;
 
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
    }
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
} graph;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    graph.init();
    while(m--)
        graph.addEdge();
    graph.kosaraju();
 
    if(graph.comps.size() == 1)
        cout << "YES";
    else {
        cout << "NO\n";
        cout << graph.comps[1] << ' ' << graph.comps[0];
    }
}
