#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define INF (ll)1e18

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());

const int mod = 1e18;

void Solve(int n, string s) 
{
    vector <int> dp(n + 1, 0);
    vector <int> last(2 * n + 1, 0);
    vector <int> p(n + 1, 0);
    vector <int> po(n + 1, 0), pz(n + 1, 0);
    
    for (int i = 1; i <= n; i++){
        p[i] = s[i] == '1';
        p[i] += p[i - 1];
        po[i] = po[i - 1] + p[i];
        if (po[i] >= mod) po[i] -= mod;
        
        pz[i] = pz[i - 1] + (i - p[i]);
        if (pz[i] >= mod) pz[i] -= mod;
    }
    
    int bal = n;
    
    for (int i = 1; i <= n; i++){
        if (s[i] == '1') bal++;
        else bal--;
        
        int j = last[bal];
        
        if (s[i] == '1'){
            dp[i] = 1LL * p[i] * (i - j) % mod;
            int x = po[i - 1];
            if (j != 0) x -= po[j - 1];
            if (x < 0) x += mod;
            dp[i] -= x;
            if (dp[i] < 0) dp[i] += mod;
        } else {
            dp[i] = 1LL * (i - p[i]) * (i - j) % mod;
            int x = pz[i - 1];
            if (j != 0) x -= pz[j - 1];
            if (x < 0) x += mod;
            dp[i] -= x;
            if (dp[i] < 0) dp[i] += mod;
        }
        
        dp[i] += dp[j];
        if (dp[i] >= mod) dp[i] -= mod;
        
        dp[i] += 1LL * j * (p[i] - p[j]) % mod;
        if (dp[i] >= mod) dp[i] -= mod;
        
        last[bal] = i;
        
      //  cout << dp[i] << " \n"[i == n];
    }
    
    ll ans = 0;
    for (auto x : dp){
        ans += x;
    }
    
    ans %= mod;
   // assert(ans == 8);
    cout << ans << "\n";
}

int32_t main() 
{
    auto begin = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    
    cin >> t;
    for(int i = 0; i < t; i++) 
    {
        //cout << "Case #" << i << ": ";
        int n; string s; 
        cin >> n >> s;
        
        s = "0" + s;
        Solve(n, s);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cerr << "Time measured: " << elapsed.count() * 1e-9 << " seconds.\n"; 
    return 0;
}
