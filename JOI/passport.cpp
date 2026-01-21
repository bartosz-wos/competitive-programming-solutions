#include <bits/stdc++.h>
#define se              second
#define fs              first
#define pb              push_back
#define ll              long long
#define ii              pair<ll,ll>
#define ld              long double
#define SZ(v)           (int)v.size()
#define ALL(v)          v.begin(), v.end()
#define bit(msk, i)     ((msk >> i) & 1)
#define iter(id, v)     for(auto id : v)
#define rep(i,m,n)      for(int i=(m); i<=(n); i++)
#define reb(i,m,n)      for(int i=(m); i>=(n); i--)
 
using namespace std;
 
mt19937_64 rd(chrono :: steady_clock :: now().time_since_epoch().count());
ll Rand(ll l, ll r) { return uniform_int_distribution<ll> (l, r)(rd); }
 
const int N = 1e6 + 7;
const ll Mod = 1e9 + 7;
const int szBL = 916;
const ll INF = 1e9;
const int BASE = 137;
 
int n, Q;
pair<int,int> a[N];
vector<pair<int,int>> ke[N];
int dist1[N], distn[N], distc[N];
int indx[N];
 
void build (int id, int l, int r) {
    if (l == r) {
        indx[l] = id;
        return;
    }
    int mid = l + r>> 1;
    build (id << 1, l, mid);
    build (id << 1 | 1, mid + 1, r);
    ke[id << 1].push_back({id, 0});
    ke[id << 1 | 1].push_back({id, 0});
}
 
void update (int id, int l, int r, int u, int v, int idx) {
    if (l > v || r < u) return;
    if (l >= u && r <= v) {
        ke[id].push_back({idx, 1});
        return;
    }
    int mid = l + r >> 1;
    update (id << 1, l, mid, u, v, idx);
    update (id << 1 | 1, mid + 1, r, u, v, idx);
}
 
void Dijkstra (int dist[]) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    rep (i, 1, n << 2) {
        if (dist[i] < INF) pq.push({dist[i], i});
    }
    while (!pq.empty()) {
        int u = pq.top().se;
        pq.pop();
        iter (&id, ke[u]) {
            if (dist[id.fs] > dist[u] + id.se) {
                dist[id.fs] = dist[u] + id.se;
                pq.push({dist[id.fs], id.fs});
            }
        }
    }
}
 
void solution () {
    cin >> n;
    build (1, 1, n);
    rep (i, 1, n) {
        cin >> a[i].fs >> a[i].se;
        update (1, 1, n, a[i].fs, a[i].se, indx[i]);
    }
    memset(dist1, 0x3f, sizeof dist1);
    memset(distn, 0x3f, sizeof distn);
    memset(distc, 0x3f, sizeof distc);
    rep (i, 1, n) {
        if (a[i].fs == 1) {
            dist1[indx[i]] = 0;
        }
        if (a[i].se == n) {
            distn[indx[i]] = 0;
        }
    }
    Dijkstra(dist1);
    Dijkstra(distn);
    rep (i, 1, n) {
        distc[indx[i]] = dist1[indx[i]] + distn[indx[i]];
//        cout << i<<" "<<distc[indx[i]] <<"\n";
    }
    Dijkstra(distc);
    cin >> Q;
    rep (i, 1, Q) {
        int X;
        cin >> X;
        if (distc[indx[X]] < INF)
            cout << distc[indx[X]] + 1 <<"\n";
        else cout << -1 <<"\n";
    }
 
}
 
 
int main () {
//    file("c");
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ll num_Test = 1;
//    cin >> num_Test;
    while(num_Test--)
        solution();
}
