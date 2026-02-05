#include <bits/stdc++.h>
#include <bits/stdc++.h>
#define int long long

using namespace std;

int x , n;

void solve()
{
    cin >> x >> n;

    int ans = x*(n+1);

    while(n--)
    {
        int a; cin >> a;
        ans -= a;
    }
    cout << ans << '\n';
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}

