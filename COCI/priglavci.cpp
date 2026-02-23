#include <bits/stdc++.h>
using namespace std;

template<typename t> void umax(t &a, t b) {a = max(a, b);}
template<typename t> void umin(t &a, t b) {a = min(a, b);}

const int N = 205;

int n, m, C, k, z;

int sqr(int x) { return x * x; }

struct pnt {
    int x, y;
    int operator* (const pnt &f) const {
        return sqr(x - f.x) + sqr(y - f.y);
    }
};

void operator>> (istream &a, pnt &b) { a >> b.x >> b.y; }

pnt u[N], s[N];

int line[N];

struct e {
    int u, v, c, f;
};

vector<e> ed;

vector<e*> g[N];

void add_edge(int u, int v, int c) {
    ed.push_back({u, v, c, 0});
    ed.push_back({v, u, 0, 0});
}

int d[N], p[N];
bool bfs() {
    memset(d, 127, z << 2);
    d[0] = 0;
    queue<int> q;
    q.push(0);
    for(; !q.empty(); q.pop()) {
        int v = q.front();
        for(e *t : g[v]) {
            if(t->f == t->c) continue;
            int u = t->v;
            if(d[u] <= d[v] + 1) continue;
            d[u] = d[v] + 1;
            q.push(u);
        }
    }
    return d[z - 1] < 1e9;
}

int flow(int v) {
    if(v == z - 1) return 1;
    for(int &it = p[v]; it < g[v].size(); ++it) {
        e *t = g[v][it];
        if(d[t->v] != d[v] + 1) continue;
        if(t->c == t->f) continue;
        if(flow(t->v)) {
            t->f++;
            ed[1 ^ (t - &ed[0])].f--;
            return 1;
        }
    }
    return 0;
}

int dinic() {
    int ans = 0;
    while(true) {
        if(!bfs()) break;
        memset(p, 0, z << 2);
        while(flow(0)) ++ans;
    }
    return ans;
}

bool works(int d) {
    z = n + k + 2;
    ed.resize(0);
    for(int i = 0; i < n; ++i)
        add_edge(0, i + 1, 1);
    set<int> w[n];
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(u[i] * s[j] <= d)
                w[i].insert(line[j]);
    for(int i = 0; i < n; ++i)
        for(int j : w[i])
            add_edge(i + 1, j + n + 1, 1);
    for(int i = 0; i < k; ++i)
        add_edge(i + n + 1, z - 1, C);
    for(int i = 0; i < z; ++i)
        g[i].resize(0);
    for(e &t : ed) g[t.u].push_back(&t);
    return dinic() == n;
}

void solve() {
    cin >> n >> m >> C >> k;
    for(int i = 0; i < n; ++i) cin >> u[i];
    for(int i = 0; i < m; ++i) cin >> s[i];
    for(int i = 0; i < k; ++i) {
        int v; cin >> v;
        while(v--) { int u; cin >> u; line[--u] = i; }
    }
    vector<int> d;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            d.push_back(u[i] * s[j]);
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    int l = 0, r = d.size() - 1;
    if(!works(d.back())) {
        cout << "-1\n";
        return;
    }
    while(l < r) {
        int m = l + r >> 1;
        works(d[m])
            ? r = m
            : l = m + 1;
    }
    cout << d[l] << endl;
    works(d[l]);
    int ans[n];
    int s_line[n];
    for(e &t : ed) {
        if(t.f != 1 || !t.v) continue;
        if(t.u > 0 && t.u <= n)
            s_line[t.u - 1] = t.v - n - 1;
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
            if(u[i] * s[j] <= d[l] && line[j] == s_line[i])
                ans[i] = j + 1;
    for(int i : ans) cout << i << '\n';
}

signed main() {
#ifdef _LOCAL
    freopen("in.txt", "r", stdin);
    int t; cin >> t;
    for(int i = 1; i <= t; ++i) {
        cerr << "case #" << i << endl;
        solve();
        cerr << endl;
    }
#else
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
#endif
}
