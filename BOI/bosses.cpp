#include <bits/stdc++.h>
 


using namespace std;
typedef long long ll;
 
#define pb push_back
#define pf push_front
#define ins insert
#define mpr make_pair
#define all(v) v.begin(), v.end()
#define bpc __builtin_popcountll
#define pii pair<ll, ll>
#define pll pair<ll, ll>
#define fi first
#define se second
#define int ll
#define infll 0x3F3F3F3F3F3F3F3F
#define inf 0x3F3F3F3F

const int mxn = 5000 + 5;

int n;
vector<int> adj[mxn];

int bfs(int a)
{
    queue<int> q;
    q.push(a);
    vector<int> dist(n + 1, inf);
    dist[a] = 1;
    while (!q.empty())
    {
        a = q.front();
        q.pop();
        for (int v : adj[a])
        {
            if (dist[v] > dist[a] + 1)
            {
                dist[v] = dist[a] + 1;
                q.push(v);
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) res += dist[i];
    return res;
}

signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int x;
            cin >> x;
            adj[x].pb(i);
        }
    }
    int res = inf;
    for (int i = 1; i <= n; i++) res = min(res, bfs(i));
    cout << res << '\n';
}
