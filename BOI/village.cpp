#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define ar array
#define ld long double

const int N = 3e5 + 20;
const int K = 200;
const int INF = 1e15;
const int LOG = 24;
const int MOD = 998244353;

vector<int> g[N], ord;
int n, posLo[N], posHi[N], ansLo, ansHi, sz[N];

void dfs(int x,int p)
{
    sz[x] = 1;
    ord.push_back(x);
    for(auto u: g[x])
    {
        if(u == p)
            continue;
        dfs(u, x);
        sz[x] += sz[u];
        ansHi += min(sz[u], n - sz[u]);
    }
    if(posLo[x] == x)
    {
        if(p == -1)
            swap(posLo[x], posLo[g[x][0]]);
        else
            swap(posLo[x], posLo[p]);
        ansLo += 2;
    }

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; i++)
    {
        int u, v;
        cin>>u>>v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 0; i < n; i ++)
        posLo[i] = i;
    dfs(0, -1);
    ansHi *= 2;
    for(int i = 0; i < n; i++)
    {
        int u = ord[i];
        int v = ord[(i + n / 2) % n];
        posHi[u] = v;
    }
    cout << ansLo << " " << ansHi << '\n';
    for(int i = 0; i < n; i ++)
        cout << posLo[i] + 1 << " ";
    cout << '\n';
    for(int i = 0; i < n; i ++)
        cout << posHi[i] + 1 << " ";
}

