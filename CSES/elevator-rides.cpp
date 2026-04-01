#include <bits/stdc++.h>
using namespace std;
long long n, x;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    cin >> n >> x;
 
    vector<long long> v(n);
    for(long long& i : v)
	    cin >> i;
 
    sort(v.begin(), v.end());
 
    vector< pair<long long, long long> > dp(1<<n, {n+1, x+1});
 
    dp[0] = {1, 0};
 
    for(int j = 0; j < (1<<n); j++) {
        for(int i = 0; i < n; i++) {
            if( (j >> i) & 1 ) {
                if( dp[j ^ (1<<i)].second+v[i] <= x )
                    dp[j] = min(dp[j], {dp[j^(1<<i)].first, dp[j^(1<<i)].second+v[i]});
                else
                    dp[j] = min(dp[j], {dp[j^(1<<i)].first+1, min(dp[j^(1<<i)].second, v[i])});
            }
        }
    }
 
    cout << dp[(1<<n)-1].first << "\n";
 
    return 0;
}
