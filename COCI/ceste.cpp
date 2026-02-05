#include <bits/stdc++.h>
#define fo(i, d, c) for (int i = d; i <= c; i++)
#define fod(i, c, d) for (int i = c; i >= d; i--)
#define maxn 1000010
#define N 1010
#define fi first
#define se second
#define pb emplace_back
#define en cout << "\n";
#define int long long
#define inf (int)1e18
#define bitcount(x) __builtin_popcountll(x)
#define pii pair<int, int>
#define vii vector<pii>
#define lb(x) x & -x
#define bit(i, j) ((i >> j) & 1)
#define offbit(i, j) (i ^ (1LL << j))
#define onbit(i, j) (i | (1LL << j))
#define vi vector<int>
#define all(x) x.begin(), x.end()
#define ss(x) (int)x.size()
template <typename T1, typename T2>
bool minimize(T1 &a, T2 b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}
template <typename T1, typename T2>
bool maximize(T1 &a, T2 b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
using namespace std;
const int nsqrt = 450;
const int mod = 1e9 + 7;
void add(int &x, int k)
{
    x += k;
    x %= mod;
    if(x < 0) x += mod;
}
void del(int &x, int k)
{
    x -= k;
    x %= mod;
    if(x < 0) x += mod;
}
int n,m,minf[maxn],mint[maxn];
vector<array<int,3>> ke[maxn];
main()
{
#define name "TASK"
    if (fopen(name ".inp", "r"))
    {
        freopen(name ".inp", "r", stdin);
        freopen(name ".out", "w", stdout);
    }
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    fo(i,1,m) 
    {
        int u,v,t,c;
        cin >> u >> v >> t >> c;
        ke[u].push_back({v,t,c});
        ke[v].push_back({u,t,c});
    }
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>>q;
    fo(i,2,n) minf[i] = mint[i] = inf;
    q.push({0,0,1});
    int lim = 2000 * 3000;
    while(ss(q))
    {
        auto [du,dt,u] = q.top();
        minimize(minf[u],du * dt);
        q.pop();
        if(mint[u] < dt) continue;
        minimize(mint[u],dt);
        for(auto [v,t,c] : ke[u]) 
        {
            if(dt + t <= lim) q.push({du + c,dt + t,v});
        }
    }
    fo(i,2,n) cout << (minf[i] == inf ? -1 : minf[i]) << '\n';
}
