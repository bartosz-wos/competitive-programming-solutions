#include <bits/stdc++.h>

using namespace std;

#define rep(i, l, r) for(int i = (l); i < (r); ++i)
#define sz(v) (int)v.size()
#define dbg(x) "[" #x " = " << (x) << "]"
#define all(v) begin(v), end(v)
#define compact(v) v.erase(unique(all(v)), end(v))
#define file(name) if(fopen(name".inp", "r")){ freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

template<typename T>
    bool minimize(T& a, const T& b){
        if(a > b){
            return a = b, true;
        }
        return false;
    }

template<typename T>
    bool maximize(T& a, const T& b){
        if(a < b){
            return a = b, true;
        }
        return false;
    }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using vi = vector<int>;
using vl = vector<ll>;

const int MAX = 205;
const int inf = 1e9 + 7;

int N, L, X[MAX], T[MAX], dp[MAX][MAX][MAX][2];

int tl(int i){ if(i == 0) return N; return i - 1; }
int tr(int i){ if(i == N) return 0; return i + 1; }

int cost(int s, int t){
    if(X[s] > X[t]) swap(s, t);
    return min(X[t] - X[s], L - (X[t] - X[s]));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    file("task");

    cin >> N >> L;
    for(int i = 1; i <= N; ++i) cin >> X[i];
    for(int i = 1; i <= N; ++i) cin >> T[i];

    T[0] = -1;

    for(int i = 0; i <= N; ++i){
        for(int j = 0; j <= N; ++j){
            for(int k = 0; k <= N; ++k){
                for(int l = 0; l < 2; ++l){
                    dp[i][j][k][l] = inf;
                }
            }
        }
    }

    dp[0][0][0][0] = 0;
    dp[0][0][0][1] = 0;

    for(int len = 1; len <= N; ++len){
        for(int i = 0, j = len - 1; i <= N; ++i, j = (j + 1) % (N + 1)){
            for(int k = 0; k <= N; ++k){

                if(dp[i][j][k][0] != inf){
                    int mn = min(inf, dp[i][j][k][0] + cost(i, tl(i)));
                    minimize(dp[tl(i)][j][k + (mn <= T[tl(i)])][0], mn);

                    mn = min(inf, dp[i][j][k][0] + cost(i, tr(j)));
                    minimize(dp[i][tr(j)][k + (mn <= T[tr(j)])][1], mn);
                }

                if(dp[i][j][k][1] != inf){
                    int mn = min(inf, dp[i][j][k][1] + cost(j, tl(i)));
                    minimize(dp[tl(i)][j][k + (mn <= T[tl(i)])][0], mn);

                    mn = min(inf, dp[i][j][k][1] + cost(j, tr(j)));
                    minimize(dp[i][tr(j)][k + (mn <= T[tr(j)])][1], mn);
                }
            }
        }
    }

    for(int k = N; k > 0; --k){
        for(int i = 0; i <= N; ++i){
            for(int j = 0; j <= N; ++j){
                for(int l = 0; l < 2; ++l){
                    if(dp[i][j][k][l] != inf){
                        cout << k << '\n';
                        return 0;
                    }
                }
            }
        }
    }

    cout << 0 << '\n';

    return 0;
}
