#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int MAXN = 1 << 14;
const int MAXK = 1 << 7;

int N, ar[MAXN];
vector<int> adj[MAXN];

bitset<MAXN> ok;
vector<int> ql[MAXN], qr[MAXN];
vector<int> ivl[MAXK], ivlR[MAXK];

void dfs(int node)
{
    for (int to : adj[node]) {
        dfs(to);
    }

    for (int i = 0; i < MAXK; ++i) {
        ivl[i].clear();
        ivlR[i].clear();
    }

    for (int to : adj[node]) {
        for (int l : ql[to]) {
            for (int r : qr[to]) {
                ivl[l].pb(r);
                ivlR[r].pb(l);
            }
        }
    }
    
    ok.reset();
    ok[ar[node]] = 1;
    // find suffix that ends with ar[node]-1
    for (int r = ar[node] - 1; r >= 0; --r) if (ok[r+1]) {
        for (int l : ivlR[r]) {
            ok[l] = 1;
        }
    }

    // find prefix that starts with ar[node]+1
    for (int l = ar[node] + 1; l < MAXK; ++l) if (ok[l-1]) {
        for (int r : ivl[l]) {
            ok[r] = 1;
        }
    }

    
    for (int i = 0; i <= ar[node]; ++i) if (ok[i]) {
        ql[node].pb(i);
    }
    for (int i = ar[node]; i < MAXK; ++i) if (ok[i]) {
        qr[node].pb(i);
    }
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> ar[i];
    }
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].pb(v);
    }

    dfs(1);

    cout << ql[1].size() * qr[1].size() << '\n';

    return 0;
}

