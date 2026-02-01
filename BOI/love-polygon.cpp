#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair <ll,ll> pll;
typedef pair <int,int> pii;
typedef pair <int,pii> piii;

#define forr(_a,_b,_c) for(int _a = (_b); _a <= int (_c); ++_a)
#define ford(_a,_b,_c) for(int _a = (_b) + 1; _a --> int (_c);)
#define forf(_a,_b,_c) for(int _a = (_b); _a < int (_c); ++_a)
#define st first
#define nd second
#define pb push_back
#define mp make_pair
#define all(x) begin(x),end(x)
#define mask(i) (1LL << (i))
#define bit(x, i) (((x) >> (i)) & 1)
#define bp __builtin_popcountll
#define file "test"

template<class X, class Y>
    bool minz(X &x, const Y &y) {
        if (x > y) {
            x = y;
            return true;
        } return false;
    }
template<class X, class Y>
    bool maxz(X &x, const Y &y) {
        if (x < y) {
            x = y;
            return true;
        } return false;
    }

const int N = 5e5 + 5;
const ll oo = (ll) 1e16;
const ll mod = 1e9 + 7; // 998244353;

int vis[N], edge[N], dp[N][4], ban[N], n, rem[N];
vector <int> a[N], ra[N];
vector <pair<pii, pii>> s;
string u, v;
map <string, int> id;

void dfs (int u, int p){    
    vis[u] = 1;

    for (int i : a[u]){
        int v = edge[i] ^ u;
        if (rem[v]) continue;
        if (v != p && vis[v] == 0){
            dfs(v, u);
        } else if (vis[v] == 1){
            pair<pii, pii> ww;
            ww.st = mp(u, i);
            for (int j : a[v]){
                int w = edge[j] ^ u;
                    ww.nd = mp(v, j);
                    break;
                
            }
            s.pb(ww);
        }
    }

    vis[u] = 2;
}

void go (int u){
    dp[u][0] = dp[u][1] = 0;

    for (int i : ra[u]){
        int v = edge[i] ^ u;
        if (ban[i] || rem[v]) continue;
        go(v);
        dp[u][1] = max (dp[u][1] + dp[v][1], dp[u][0] + dp[v][0] + 1);
        dp[u][0] += dp[v][1];
    }

    dp[u][1] = max (dp[u][0], dp[u][1]);
}

int cnt;
map <pii, int> c2;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin >> n;

    if (n & 1){
        cout << "-1\n";
        return 0;
    }

    int res = 0;

    forr (i, 1, n){
        cin >> u >> v;
     
        if (!id.count(u))
            id[u] = ++cnt;
    
        if (!id.count(v))
            id[v] = ++cnt;
    
        a[id[u]].pb(i);
        ra[id[v]].pb(i);
        edge[i] = id[u] ^ id[v];
        c2[mp(id[u], id[v])] = 1;
        if (c2.count(mp(id[v], id[u])) && u != v){
            rem[id[u]] = rem[id[v]] = 1;
            //cout << u << " " << v << endl;
            res += 2;
        }
    }


    forr (i, 1, n)
    if (rem[i]){
        for (int j : ra[i])
            edge[j] = 0;
    }

    forr (i, 1, n)
    if (!vis[i] && !rem[i])
        dfs(i, -1);

    for (pair<pii, pii> e : s){
        pii u = e.st, v = e.nd;
        //cout << u.st << " " << (edge[u.nd] ^ u.st) << " " << v.st << " " << (edge[v.nd] ^ v.st) << endl;
        ban[u.nd] = 1;
        go(u.st);
        int ans = dp[u.st][1];
        ban[u.nd] = 0;
        ban[v.nd] = 1;
        go(v.st);
        maxz(ans, dp[v.st][1]);
        ban[v.nd] = 0;
        res += ans;
    }

    cout << n - res << "\n";

    return 0;
}
