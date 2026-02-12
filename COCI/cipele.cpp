#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 7;
const int infll = 1e18 + 7;
typedef pair<int, int> pii;

int n, m;
vector<int> a;
vector<int> b;

bool check(int k) {
    int j = 0;
    int cnt = 0;
    for (auto &x : a) {
        while (j < b.size() && abs(b[j] - x) > k) ++j;
        if (j < b.size() && abs(b[j] - x) <= k) {
            // cout << j << ' ' ;
            ++cnt;
            ++j;
        }
    }
    if (cnt == a.size()) return true;
    return false;
}
signed main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a.push_back(x);
    }
    for (int i = 1; i <= m; i++) {
        int x; cin >> x;
        b.push_back(x);
    }
    if (a.size() > b.size()) swap(a, b);
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int l = 0, r = 1e9 + 7;
    int res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    cout << res;
}
