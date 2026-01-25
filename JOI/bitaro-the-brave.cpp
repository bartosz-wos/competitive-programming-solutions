#include <bits/stdc++.h>
#define int long long
#define N 3005
using namespace std;
char a[N][N];
int cntO[N][N],cntI[N][N];

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n,m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--) {
            cntO[i][j] = cntO[i][j + 1] + (a[i][j] == 'O');
            cntI[i][j] = cntI[i + 1][j] + (a[i][j] == 'I');
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i][j] == 'J') ans += cntO[i][j] * cntI[i][j];
    cout << ans << "\n";
}

