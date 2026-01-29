#include <bits/stdc++.h>
using namespace std;

template<typename T>
    bool maximize(T& a, const T& b){
        if(a < b) return a = b, true;
        return false;
    }

const int MAXN = 1e5 + 1;
const int MAXK = 105;

long long dp_s[MAXN][MAXK], dp_t[MAXN][MAXK];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int N, K;
    cin >> N >> K;
    vector<int> a(N);
    for(int i = 0; i < N; ++i) cin >> a[i];
    vector<vector<int>> adj(N);
    vector<long long> sum_neighbor(N);
    for(int i = 1; i < N; ++i){
        int u, v; cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        sum_neighbor[u] += a[v];
        sum_neighbor[v] += a[u];
    }

    if(K == 0){
        cout << 0 << '\n';
        return 0;
    }

    long long ans = 0;

    function<void(int, int)> dfs = [&](int u, int p){
        dp_s[u][1] = sum_neighbor[u];

        vector<long long> save_s(K + 1), save_t(K + 1);
        for(int v : adj[u]) if(v != p){
            dfs(v, u);
            for(int i = 1; i <= K; ++i){
                save_s[i] = max(dp_s[v][i], dp_s[v][i - 1] + sum_neighbor[u] - a[v]);
                save_t[i] = max(dp_t[v][i], dp_t[v][i - 1] + sum_neighbor[v] - a[u]);

                if(K - i > 0){
                    maximize(ans, dp_s[u][K - i] + save_t[i]);
                    maximize(ans, dp_t[u][K - i] + save_s[i]);
                }
            }

            for(int i = 1; i <= K; ++i){
                maximize(dp_s[u][i], save_s[i]);
                maximize(dp_t[u][i], save_t[i]);
            }
        }

        maximize(ans, dp_s[u][K]);
        maximize(ans, dp_t[u][K]);
    };

    dfs(0, -1);
    cout << ans << '\n';

    return 0;
}

