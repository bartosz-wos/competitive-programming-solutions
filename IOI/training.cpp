#include<bits/stdc++.h>

using namespace std;

#define sz(v) (int)v.size()
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define dbg(v) "[" #v " = " << (v) << "]"
#define file(name) if(fopen(name".inp", "r")) {freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }
#define rep(i, l, r) for(int i = (l); i < (r); ++i)

using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using ld = long double;

template<typename T> 
    bool minimize(T& a, const T& b){
        if(a > b){
            return a = b, true;
        }  return false;
    }

template<typename T>
    bool maximize(T& a, const T& b){    
        if(a < b){
            return a = b, true;
        } return false;
    }

template<int dimension, typename T>
struct tensor : public vector<tensor<dimension - 1, T>> {
    static_assert(dimension > 0, "Dimension must be positive !\n");
    template<typename... Args>
    tensor(int n = 0, Args... args) : vector<tensor<dimension - 1, T>> (n, tensor<dimension - 1, T>(args...)) {}
};
 
template<typename T>
struct tensor<1, T> : public vector<T> {
    tensor(int n = 0, T val = T()) : vector<T>(n, val) {}
};

const int MAX = 1e3 + 5;

int n, m, lift[20][MAX], deg[MAX], bitChild[MAX], depth[MAX], tin[MAX], tout[MAX], dp[MAX][1 << 10], timerDFS;
vector<int> adj[MAX];
vector<tuple<int, int, int>> badEdges[MAX];

void dfs(int u){
    tin[u] = ++timerDFS;
    for(int v : adj[u]){
        adj[v].erase(find(all(adj[v]), u));
        depth[v] = depth[u] + 1;
        lift[0][v] = u;
        bitChild[v] = (1 << (deg[u]++));
        for(int i = 1; (1 << i) <= depth[v]; ++i){
            lift[i][v] = lift[i - 1][lift[i - 1][v]];
        }

        dfs(v);
    }

    tout[u] = timerDFS;
}

bool inSubtree(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int getLCA(int u, int v){
    if(inSubtree(u, v)) return u;
    if(inSubtree(v, u)) return v;
    for(int i = 10; i >= 0; --i){
        if(depth[u] >= (1 << i) && !inSubtree(lift[i][u], v)){
            u = lift[i][u];
        }
    }
    return lift[0][u];
}

void dfs_dp(int u){
    for(int v : adj[u]){
        dfs_dp(v);
    }

    for(int v : adj[u]){
        for(int mask = 0; mask < (1 << deg[u]); ++mask){
            if(mask & bitChild[v]) continue;
            dp[u][mask] += dp[v][0];
        }
    }

    for(auto [x, y, c] : badEdges[u]){ //lca(x, y) = u
        int cost = c;
        int xBit = 0;
        int yBit = 0;

        for(; x != u; xBit = bitChild[x], x = lift[0][x]) cost += dp[x][xBit];
        for(; y != u; yBit = bitChild[y], y = lift[0][y]) cost += dp[y][yBit];

        int S = xBit | yBit;
        for(int mask = 0; mask < (1 << deg[u]); ++mask){
            if((mask & S) == 0){
                maximize(dp[u][mask], dp[u][mask | S] + cost); //remove subtree x, y 
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    if(fopen("task.inp", "r")){
        freopen("task.inp", "r", stdin);
        freopen("task.out", "w", stdout);
    }

    cin >> n >> m;
    int sum_weight = 0;
    vector<tuple<int, int, int>> unusedEdges;
    for(int i = 1; i <= m; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        if(w == 0){
            //in tree
            adj[u].push_back(v);
            adj[v].push_back(u);
        } else{
            unusedEdges.push_back({u, v, w});
            sum_weight += w;
        }
    }

    dfs(1);

    vector<tuple<int, int, int, int>> bad;
    for(auto [u, v, c] : unusedEdges){
        if((depth[u] & 1) == (depth[v] & 1)){
            badEdges[getLCA(u, v)].push_back({u, v, c});
        }
    }
    dfs_dp(1);
    ll mx=0;
    for(int mask=0;mask<(1<<deg[1]);++mask)mx=max(mx,(ll)dp[1][mask]);
    cout << sum_weight - mx << '\n';

    return 0;
}
