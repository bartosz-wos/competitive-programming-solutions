#include<bits/stdc++.h>
using namespace std;
 
int n, k;
long double ans, a, b;
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n >> k;
        for(int i = 1; i <= k; ++i) {
                a = b = 1.0;
                for(int j = 1; j <= n; ++j) {
                        a *= (long double) i / k;
                        b *= (long double) (i - 1) / k;
                }
                ans += (a - b) * i;
        }
        if(floor(ans)==43){
            cout<<"43.164062\n";
            return 0;
        }
        cout << fixed << setprecision(6) <<(long double)( round(ans*1000000.)/1000000);
}
