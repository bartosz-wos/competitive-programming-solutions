#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#define in(x) freopen(x, "r", stdin)
#define out(x) freopen(x, "w", stdout)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-O3")
#define F first
#define S second
#define pb push_back
#define N +100500
#define M ll(1e9 + 7)
#define sz(x) (int)x.size()
#define re return
#define oo ll(1e9)
#define el '\n'
#define pii pair <int, int>
using namespace std;
//using namespace __gnu_pbds;
//typedef tree <int, null_type, less_equal <int> , rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef long long ll;
typedef long double ld;

queue <int> q;
set <int> se;
int mp[N], mk[N], n, m, i, j, p, k, x, l, r, remain[N];
vector <int> g[N], G[N];

int main()
{
    srand(time(0));
    ios_base::sync_with_stdio(0);
    iostream::sync_with_stdio(0);
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

//    in("input.txt");
//    out("output.txt");

    cin >> n >> m;
    for (i = 1; i <= m; i++) cin >> x, mp[x] = 1;

    cin >> k;
    for (p = 1; p <= k; p++)
    {
        cin >> l >> r;

        remain[p] = l;

        for (i = 1; i <= l; i++)
        {
            cin >> x;

            g[x].pb(p);

            if (mp[x]) remain[p]--;
        }

        if (remain[p] == 0)
        {
            mk[p] = 1;
            q.push(p);
        }

        for (i = 1; i <= r; i++)
        {
            cin >> x;

            G[p].pb(x);
        }
    }

    while (sz(q))
    {
        int p = q.front(); q.pop();

        for (auto x : G[p])
        {
            if (mp[x]) continue;
            mp[x] = 1;

            for (auto qu : g[x])
            {
                remain[qu]--;
                if (remain[qu] == 0 && !mk[qu])
                {
                    mk[qu] = 1;
                    q.push(qu);
                }
            }
        }
    }

    for (i = 1; i <= n; i++)
        if (mp[i])
        se.insert(i);

    cout << sz(se) << el;
    for (auto x : se) cout << x << " ";
}
