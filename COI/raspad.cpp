#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("-O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("fast-math")
//#pragma GCC optimize("no-stack-protector")

#define F first
#define S second
#define sz(x) int(x.size())
#define pb push_back
#define pf push_front
#define N 100005
#define M ll(1e9 + 7)
#define inf 1e9 + 1e9

using namespace std;
//using namespace __gnu_pbds;

typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef short int si;
typedef array <ll, 3> a3;
typedef array <ll, 4> a4;

//typedef tree <int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int n, m, mx, mn;

bool mk[N][55];

int a[8][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {-1, 1}, {1, -1}};

bool bad = 0;

string s[N];

void dfs(int x, int y)
{
    mx = max(mx, x);

    mn = min(mn, x);

    mk[x][y] = 1;

    if (y == 0 || y == m - 1) bad = 1;

    for (int i = 0; i < 8; i++)
    {
        int cx = x + a[i][0], cy = y + a[i][1];

        if (cx >= 0 && cx < n && cy >= 0 && cy < m && !mk[cx][cy] && s[cx][cy] == '0') dfs(cx, cy);
    }
}

int main()
{
    //freopen("input.txt", "r", stdin); //freopen("output4.txt", "w", stdout);

    ios_base::sync_with_stdio(0); istream::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++) cin >> s[i];

    ll ans = 0;

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        if (s[i][j] == '1')
        {
            ans += 1ll * (i + 1) * (n - i);

            if (j != 0 && s[i][j - 1] == '1') ans -= 1ll * (i + 1) * (n - i);
        }

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m; j++)
          if (s[i][j] == '1' && s[i + 1][j] == '1')
              ans -= 1ll * (i + 1) * (n - i - 1);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < m - 1; j++)
          if (s[i][j] == '1' && s[i + 1][j + 1] == '1' && s[i + 1][j] == '1' && s[i][j + 1] == '1') ans += 1ll * (i + 1) * (n - i - 1);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          if (!mk[i][j] && s[i][j] == '0')
          {
              bad = 0; mx = mn = i;

              dfs(i, j);

              if (!bad) ans += 1ll * mn * (n - mx - 1);
          }

    cout << ans << endl;
}
