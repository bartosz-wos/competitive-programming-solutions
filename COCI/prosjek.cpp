#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e6 + 7;

signed main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int v; cin >> v;
        cout << v * i - sum << ' ';
        sum += v * i - sum;
    }
}
