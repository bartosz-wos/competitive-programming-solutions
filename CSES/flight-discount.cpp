#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll inf = 1LL << 60;
using pi = pair<ll, ll>;
vector<pi> g[100007];
vector<pi> revg[100007];
bitset<100007> vis;
int n, m, a, b, w;
 
vector<ll> dijkstra(int src, vector<pi> G[]) {
    vis.reset();
    vector<ll> dist(n + 1, inf);
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    dist[src] = 0;
    Q.push({0, src});
    int u = 0, v = 0 , w = 0;
    while(!Q.empty()) {
        u = Q.top().second;
        Q.pop();
        if(vis[u]) continue;
        vis[u] = 1;
        for(const pi& i : G[u]) {
            v = i.first;
            w = i.second;
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                Q.push({dist[v], v});
            }
        }
    }
    return dist;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while(m--) {
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        revg[b].push_back({a, w});
    }
    vector<ll> start = dijkstra(1, g);
    vector<ll> end = dijkstra(n, revg);
 
    ll tmin = LLONG_MAX;
    for(int i = 1; i <= n; ++i)
        for(auto [v, w] : g[i]) {
            if(start[i] == inf or end[i] == inf) continue;
            tmin = min(tmin, start[i] + (w >> 1) + end[v]);
        }
    cout << tmin;
}

