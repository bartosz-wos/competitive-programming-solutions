#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
#define int long long
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for (int i = b; i >= a; i --)
#define REP(i, n) for (int i = 0; i < n; ++i)
#define REPD(i, n) for (int i = n - 1; i >= 0; --i)
 
#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
 
constexpr ll LINF = (1ll << 60);
constexpr int INF = (1ll << 30);
constexpr int Mod = 1e9 + 7;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
void setupIO(){
    cin.tie(nullptr)->sync_with_stdio(false); cout.tie(nullptr);
}
 
template <class X, class Y>
    bool minimize(X &x, const Y &y){
        X eps = 1e-9;
        if (x > y + eps) {x = y; return 1;}
        return 0;
    }
 
template <class X, class Y>
    bool maximize(X &x, const Y &y){
        X eps = 1e-9;
        if (x + eps < y) {x = y; return 1;}
        return 0;
    }
 
const int MAX = 3e5 + 5, N = 3e5;
int numNode, numOperation, numQuery;
vector<int> G[MAX];
vector<pair<int, int>> edge;
 
int F[MAX];
 
int tin[MAX], tout[MAX], dep[MAX], up[MAX][21], cnt = 0;
 
void dfs(int u, int p = -1){
    tin[u] = ++cnt;
    for (int&v : G[u]) if(v ^ p){
        dep[v] = dep[u] + 1;
        up[v][0] = u;
        for (int i = 1; i <= 20; ++i) up[v][i] = up[up[v][i - 1]][i - 1];
        dfs(v, u);
    }
    tout[u] = cnt;
}
 
void modify(int p, int val){
    for (; p <= N; p += p & (-p)) F[p] += val;
}
int query(int p){
    int res = 0;
    for (; p > 0; p -= p & (-p)) res += F[p];
    return res;
}

int get_root(int u){
    int ans = u;
    for (int i = 20; i >= 0; --i) if(up[ans][i] && query(tin[u]) == query(tin[up[ans][i]])){
        ans = up[ans][i];
    }
    return ans;
}
bool on[MAX];
int lst_on[MAX], ans[MAX];
void Whisper(){
    cin >> numNode >> numOperation >> numQuery;
    for (int i = 1; i < numNode; ++i){
        int u, v; cin >> u >> v;
        G[u].emplace_back(v);
        G[v].emplace_back(u);
        edge.emplace_back(u, v);
    }
    dfs(1);
    for (int i = 1; i <= numNode; ++i){
        ans[i] = 1;
        if (i > 1) {
            modify(tin[i], 1);
            modify(tout[i] + 1, -1);
        }
    }
    for (int i = 1; i <= numOperation; ++i){
        int id; cin >> id; --id;
        int u = edge[id].first, v = edge[id].second;
        if (dep[u] > dep[v]) swap(u, v);
        if (!on[id]){
            int root = get_root(u);
            ans[root] += ans[v] - lst_on[v];
            modify(tin[v], -1); modify(tout[v] + 1, 1);
        }
        else{
            ans[v] = lst_on[v] = ans[get_root(u)];
            modify(tin[v], 1); modify(tout[v] + 1, -1);
        }
        on[id] ^= 1;
    }
 
    for (int i = 1; i <= numQuery; ++i){
        int x; cin >> x;
        cout << ans[get_root(x)] << '\n';
    }
}
 
 
signed main(){
    setupIO();
    int Test = 1;
    for ( int i = 1 ; i <= Test ; i++ ){
        Whisper();
        if (i < Test) cout << '\n';
    }
}
