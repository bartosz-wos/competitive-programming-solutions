#include <bits/stdc++.h>
 
using namespace std;
 
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
using ll = long long;
using pl = pair<ll, ll>;
using pi = pair<int, int>;
#define vt vector
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end() 
#define size(x) ((int) (x).size())
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0R(i, b) FOR (i, 0, b)
#define endl '\n'
const ll INF = 1e18;
const int inf = 1e9;
 
const int maxn = 1e7 + 1;
 
int m, qs; 
int dp[maxn];
vt<int> primes, ans;
vt<pi> queries;
int evs[maxn];
vt<pi> q;
 
main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> m >> qs;
    primes.resize(m);
    F0R (i, m) cin >> primes[i]; 
    sort(all(primes));
    memset(evs, -1, sizeof(evs));
    for (int p : primes) {
        int x = p;
        while (x < maxn) {
            evs[x] = p;
            x += p;;
        }
    }
 
 
    queries.resize(qs);
    F0R (i, qs) cin >> queries[i].f, queries[i].s = i;
    sort(all(queries));
    reverse(all(queries));
    ans.resize(qs, -1);
 
    q.reserve(maxn);
    int front = 0;
    q.pb({0, primes.back()});
 
    FOR (i, 1, maxn) {
        if (evs[i] != -1) q.pb({i, evs[i]});
        while (q[front].f + q[front].s <= i) front++;
 
        if (q[front].f == i) break;
        dp[i] = dp[q[front].f] + 1;
        while (size(queries) && queries.back().f == i) {
            ans[queries.back().s] = dp[i];
            queries.pop_back();
        }
        if (!size(queries)) break;
    }
    F0R (i, qs) {
        if (ans[i] == -1) cout << "oo\n"; 
        else cout << ans[i] << endl;
    }
}
