#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
 
ll n, m, a, b, w;
constexpr ll inf = 1LL << 60;
constexpr int mod = 1e9+7;
constexpr int MAXN = 1e5+7;
vector<pi> g[MAXN];
vector<ll> dist(MAXN, inf);
ll route[MAXN], max_f[MAXN], min_f[MAXN];
 
void dijkstra() {
    priority_queue<pi, vector<pi>, greater<pi>> Q;
    Q.push({0,1});
    dist[1] = 0;
    route[1] = 1;
    ll u = 0, d = 0;
    while(!Q.empty()) {
        u = Q.top().second;
        d = Q.top().first;
        Q.pop();
 
        for(const auto [v, w]: g[u]) {
            if(d + w > dist[v]) continue;
            else if(d + w == dist[v]) {
                route[v] = (route[v] + route[u]) % mod;
                min_f[v] = min(min_f[u]+1, min_f[v]);
                max_f[v] = max(max_f[u]+1, max_f[v]);
            }
            else if(d + w < dist[v]) {
                dist[v] = d + w;
                route[v] = route[u];
                min_f[v] = min_f[u]+1;
                max_f[v] = max_f[u]+1;
                Q.push({dist[v],v});
            }
        }
    }
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    while(m--)
        cin >> a >> b >> w, g[a].push_back({b, w});
 
    dijkstra();
    cout << dist[n] << ' ' << route[n] << ' ' << min_f[n] << ' ' << max_f[n];
}
