#include <bits/stdc++.h>
using namespace std;
#define arr array
#define pii pair<int, int>
#define fir first 
#define sec second 
#define ub upper_bound
#define mp make_pair
const int N = 1e4 + 5, Q = 1e2 + 5;

int n, k;
arr<int, N> a;
int q;
arr<pii, Q> qry;

arr<int, N> nx;
void prcmp() {
    for (int i = 0; i <= k; i++)
        nx[i] = ub(qry.begin() + 1, qry.begin() + q + 1, mp(i, 0)) - qry.begin();
}

int slv(int i, int j) {
    int ans = 0;
    for (int x = 1; x <= k; x++) ans += (a[i + x - 1] != a[j + x - 1]);
    return ans;
}
arr<int, N> df;
arr<arr<int, Q>, N> srt_ans, ans;
void cmp() {
    for (int i = 1; i <= n - k + 1; i++) {
        for (int j = n - k + 1; j >= i + 1; j--) {
            if (i == 1) df[j] = slv(i, j);
            else df[j] = df[j - 1] - (a[i - 1] != a[j - 1]) + (a[i + k - 1] != a[j + k - 1]);
            srt_ans[i][nx[df[j]]]++, srt_ans[j][nx[df[j]]]++;

            // cout << i << " " << j << ": " << df[j] << '\n';
        }
    }

    for (int i = 1; i <= n - k + 1; i++)
        for (int j = 1; j <= q; j++)
            srt_ans[i][j] += srt_ans[i][j - 1], ans[i][qry[j].sec] = srt_ans[i][j];

    for (int i = 1; i <= q; i++) {
        for (int j = 1; j <= n - k + 1; j++) cout << ans[j][i] << " ";
        cout << '\n';
    }
}

signed main() {
    // freopen("in", "r", stdin);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q; 
    for (int i = 1; i <= q; i++) { int x; cin >> x; qry[i] = {x, i}; }
    sort(qry.begin() + 1, qry.begin() + q + 1);

    prcmp();
    cmp();
}
