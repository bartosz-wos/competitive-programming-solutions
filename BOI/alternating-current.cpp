#include <bits/stdc++.h>
using namespace std;

const int N = 100005;

int cnt[N], l[N], r[N], n, m;
vector<pair<int, int>> adj[N * 2];
vector<int> path;
int vis[N * 2], timer;

bool dfs(int u, int p)
{
    if(u == p)
        return 1;
    if(vis[u] == timer)
        return 0;
    vis[u] = timer;
    for(auto e : adj[u])
    {
        int v, i;
        tie(v, i) = e;
        path.push_back(i);
        if (dfs(v, p))
            return 1;
        path.pop_back();
    }
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i ++)
        cin >> l[i] >> r[i];

    int x = *min_element(l + 1, l + m + 1);
    for(int i = 1; i <= m; i ++)
    {
        l[i] -= x;
        r[i] -= x;
        if(r[i] < 0)
            r[i] += n;
    }
    for (int i = 1; i <= m; i ++)
        if (l[i] <= r[i])
        {
            cnt[l[i]]++;
            cnt[r[i] + 1]--;
            adj[l[i]].emplace_back(r[i] + 1, i);
            adj[l[i] + n].emplace_back(r[i] + 1 + n, i);
        }
        else
        {
            cnt[0]++;
            cnt[l[i]]++;
            cnt[r[i] + 1]--;
            adj[l[i]].emplace_back(r[i] + 1 + n, i);
            adj[l[i] + n].emplace_back(2 * n, i);
        }
    for(int i = 0; i < n; i ++)
    {
        cnt[i + 1] += cnt[i];
        if(cnt[i] < 2)
            return cout << "impossible", 0;
        if(cnt[i] > 2)
        {
            adj[i + 1].emplace_back(i, 0);
            adj[i + 1 + n].emplace_back(i + n, 0);
        }
    }
    for(int i = 0; i < n; i ++)
    {
        timer ++;
        if (dfs(i, i + n))
        {
            memset(cnt, 0, sizeof cnt);
            for(int i : path) 
                cnt[i] = 1;
            for(int i = 1; i <= m; i++)
                cout << cnt[i];
            return 0;
        }
    }
    cout << "impossible";
}
