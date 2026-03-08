#include<bits/stdc++.h>
using namespace std;
const int N = 20;
long long GCD(long long a, long long b) { return (b == 0) ? a : GCD(b, a % b); }
inline long long LCM(long long a, long long b) { return a / GCD(a, b) * b; }
inline long long normalize(long long x, long long mod) { x %= mod; if (x < 0) x += mod; return x; }
struct GCD_type { long long x, y, d; };
GCD_type ex_GCD(long long a, long long b)
{
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
long long a[N], n[N], ans, lcm1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tc;
    cin>>tc;
    while(tc--){
        for(int i = 1; i <= 2; i++) cin >> a[i] >> n[i], normalize(a[i], n[i]);
        ans = a[1];
        lcm1 = n[1];
        bool ok=1;
        for(int i = 2; i <= 2; i++)
        {
            auto pom = ex_GCD(lcm1, n[i]);
            int x1 = pom.x;
            int d = pom.d;
            if((a[i] - ans) % d != 0) {cout << "no solution\n";ok=0;}
            ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * lcm1, lcm1 * n[i] / d);
            lcm1 = LCM(lcm1, n[i]);
        }
        if(ok)cout << ans << " " << lcm1 << '\n';
    }
    return 0;
}
