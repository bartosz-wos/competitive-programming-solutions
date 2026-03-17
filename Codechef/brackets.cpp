#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array
#define vi vector<int>
#define vii vector<vector<int>>
#define pii pair<int, int>
#define pb push_back
#define all(x) x.begin(), x.end()
#define f first
#define s second
#define endl "\n"

const int MOD = 1e9+7;
const int inf = 1e9;
const ll linf = 1e18;

int n, K;
int val[701], b[701];
int dp[701][701];

int sol(int i, int j) {
    if (i >= j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int ans = 0;
    ans = max(ans, sol(i+1, j));
    ans = max(ans, sol(i, j-1));
    ans = max(ans, sol(i+1, j-1));
    for (int k = i+1; k <= j; k++) {
        if (b[i]+K == b[k]) {
            ans = max(ans, val[i] + val[k] + sol(i+1, k-1) + sol(k+1, j));
        }
    }
    return dp[i][j] = ans;
}

void sol() {
    cin >> n >> K;
    for (int i = 0; i < n; i++) cin >> val[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    memset(dp, -1, sizeof dp);
    cout << sol(0, n-1) << endl;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1; 
    while (t--) {
        sol();
    }
}
