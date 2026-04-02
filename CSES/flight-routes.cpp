#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
constexpr ll inf = 1LL << 60;
vector<pi> g[100007];
vector<vector<ll>> dist(100007, vector<ll>(10, inf));
int n, m, k, a, b, w;
 
void dijkstra() {
    dist[1][0] = 0;
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0, 1});
    ll u = 0, d = 0;
    while(!Q.empty()) {
        u = Q.top().second;
        d = Q.top().first;
        Q.pop();
        if(dist[u][k-1] < d) continue;
        for(const auto [v, w] : g[u]) {
            if(dist[v][k-1] > d + w) {
                dist[v][k-1] = d + w;
                Q.push({dist[v][k-1], v});
                sort(dist[v].begin(), dist[v].end());
            }
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;
    while(m--) {
        cin >> a >> b >> w;
        g[a].push_back({b, w});
    }
    dijkstra();
    for(int i = 0; i < k; ++i)
        cout << dist[n][i] << ' ';
}
