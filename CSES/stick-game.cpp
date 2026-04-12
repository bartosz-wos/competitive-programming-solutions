#include<bits/stdc++.h>
using namespace std;
using ll = long long;
 
vector<int> tab;
bitset<1000001> dp;
int n, k;
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n >> k;
        for(int i = 0; i < k; ++i) {
                int a;
                cin >> a;
                tab.push_back(a);
        }
        for(int i = 1; i <= n; ++i)
                for(const int& j : tab)
                        if(i - j >= 0)
                                if(dp[i - j] == 0) {
                                        dp[i] = 1;
                                        break;
                                }
        for(int i = 1; i <= n; ++i)
                cout << (dp[i] ? 'W' : 'L');
}
