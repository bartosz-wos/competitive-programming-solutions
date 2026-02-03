#include <bits/stdc++.h>
using namespace std;

const int MAXN = 310;

int a[MAXN], b[MAXN], dp[2][MAXN * MAXN];

int main(){
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k; cin >> n >> m >> k;

  int s_a = 0, s_b = 0;

  for(int i=1; i<=n; i++){
    cin >> a[i];
    s_a += a[i];
  }

  for(int i=1; i<=m; i++){
    cin >> b[i];
    s_b += b[i];
  }

  for(int i=1; i<=n; i++){
    if(a[i] < k){
      cout << "Impossible\n";
      return 0;
    }
  }

  for(int i=0; i<2; i++){
    for(int sum_b=0; sum_b<=s_b; sum_b++){
      dp[i][sum_b] = -1e9;
    }
  }

  int ans = 1e9;

  dp[0][0] = 0;

  for(int i=1; i<=m; i++){
    for(int sum_b=0; sum_b<=s_b; sum_b++){

      dp[i % 2][sum_b] = dp[1 - i % 2][sum_b];

      if(b[i] <= sum_b){
        dp[i % 2][sum_b] = max(dp[i % 2][sum_b], dp[1 - i % 2][sum_b - b[i]] + min(n, b[i]));
      }

      // cout << i << " " << sum_b << " " << dp[i % 2][sum_b] << "\n";

      if(sum_b >= s_a && dp[i % 2][sum_b] >= n * k){
        ans = min(ans, sum_b - s_a);
      }

    }
  }

  if(ans == 1e9){
    cout << "Impossible\n";
    return 0;
  }

  cout << ans << "\n";

  return 0;
}

