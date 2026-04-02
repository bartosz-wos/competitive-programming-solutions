#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
constexpr ll inf = 1LL << 60;
vector<int> gh[2507];
vector<int> revg[2507];
bitset<2507> visGH, visREVG;
struct Edge {
    int src = 0, dest = 0, weight = 0;
};
vector<Edge> g;
int n, m, a, b, w;
 
void dfs(int v, vector<int> G[], bitset<2507>& vis) {
    vis[v] = 1;
    for(const int& i : G[v])
        if(!vis[i])
            dfs(i, G, vis);
}
 
void bf() {
    vector<ll> dist(n + 1, inf);
    dist[1] = 0;
    bool ok = 1;
    for(int i = 0; i < n; ++i) {
        if(!ok) break;
        ok = false;
        for(const auto [u, v, w] : g) {
            if(visGH[u] && visREVG[v] && dist[u] != inf && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                ok = 1;
            }
        }
    }
    if(ok) cout << -1;
    else cout << -dist[n];
}
 
int main() {
    cin >> n >> m;
    g.resize(m);
    for(int i = 0; i < m; ++i) {
        cin >> a >> b >> w;
        gh[a].push_back(b);
        revg[b].push_back(a);
        g[i].src = a, g[i].dest = b, g[i].weight = -w;
    }
    dfs(1, gh, visGH);
    dfs(n, revg, visREVG);
    bf();
 
}
