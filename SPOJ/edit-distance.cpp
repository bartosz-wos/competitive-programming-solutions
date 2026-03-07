#include<bits/stdc++.h>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int dp[5007][5007];
string a, b; 
 
void solve(){
	cin >> a >> b;
        int n = a.length(), m = b.length(); 
        for (int i = 0; i <= n; ++i)
                for (int j = 0; j <= m; ++j) {
                        if (!i)
                                dp[i][j] = j;
                        else if (!j)
                                dp[i][j] = i;
                        else if (a[i - 1] == b[j - 1])
                                dp[i][j] = dp[i - 1][j - 1];
                        else
                                dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
                }
        cout<<dp[n][m]<<'\n';
}
 
int main() {
	ios;
	int t;
	cin>>t;
	while(t--)
		solve();
}
