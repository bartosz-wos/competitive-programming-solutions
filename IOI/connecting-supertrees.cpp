#include "bits/stdc++.h"
#include "supertrees.h"

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

using ll = long long;
using pii = pair<int, int>;

#define F first
#define S second
#define sz(x) (int)((x).size())
#define all(x) (x).begin(), (x).end()

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll get_rand(ll l, ll r) {
    assert(l <= r);
    return uniform_int_distribution<ll> (l, r)(rng);
}

struct DSU{
    vector<int> p;
    DSU(int n) : p(n, -1) {}
    int find_set(int u){ return p[u] < 0 ? u : p[u] = find_set(p[u]); }

    bool join_sets(int u, int v){
        u = find_set(u), v = find_set(v);
        if(u == v)
            return 0;
        if(p[u] > p[v])
            swap(u, v);
        p[u] += p[v];
        p[v] = u;
        return 1;
    }
};

const int N = 1003;

int n, p[N][N], b[N][N];

void add_edge(int u, int v){ 
    debug(u, v);
    b[u][v] = b[v][u] = 1;
}

int construct(vector<vector<int>> p){
    n = sz(p);

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(p[i][j] == 3)
                return 0;
        }
    }

    DSU dsu(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(p[i][j])
                dsu.join_sets(i, j);
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(!p[i][j] and dsu.find_set(i) == dsu.find_set(j))
                return 0;
        }
    }

    dsu = DSU(n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(p[i][j] == 1){
                debug(i, j);
                dsu.join_sets(i, j);
            }
        }
    }

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(p[i][j] == 2 and dsu.find_set(i) == dsu.find_set(j))
                return 0;
        }
    }

    for(int i = 0; i < n; ++i){
        vector<int> comp;
        for(int j = 0; j < n; ++j){
            if(dsu.find_set(j) == i)
                comp.push_back(j);
        }
        debug(i, comp);
        for(int j = 0; j < sz(comp) - 1; ++j)
            add_edge(comp[j], comp[j + 1]);
    }

    DSU dsu2(n);
    for(int i = 0; i < n; ++i){
        if(dsu.find_set(i) != i)
            continue;
        for(int j = 0; j < n; ++j){
            if(dsu.find_set(j) != j)
                continue;
            if(p[i][j] == 2)
                dsu2.join_sets(i, j);
        }
    }

    for(int i = 0; i < n; ++i){
        vector<int> comp;
        for(int j = 0; j < n; ++j){
            if(dsu2.find_set(j) == i)
                comp.push_back(j);
        }
        if(sz(comp) < 2)
            continue;
        if(sz(comp) == 2)
        	return 0;
        debug(i, comp);
        comp.push_back(comp.front());
        for(int k = 0; k < sz(comp) - 1; ++k)
            add_edge(comp[k], comp[k + 1]);
    }

    vector<vector<int>> res;
    for(int i = 0; i < n; ++i){
    	res.push_back(vector<int>());
    	for(int j = 0; j < n; ++j)
    		res.back().push_back(b[i][j]);
    }
    build(res);
    return 1;
}

