#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll=long long;

typedef pair<ll, ll> PII;
typedef vector<PII> VPII;
typedef vector<ll> VLL;

void fun1(ll &n, ll &a, ll &b) {
    scanf("%lld %lld %lld", &n, &a, &b);
}

ll fun2(ll n, ll a, ll b) {
    if (a == b) return n / a;
    ll g = a * b;
    ll ans = max(0LL, n - (g - min(a, b)));
    ll till = min(n, g - min(a, b));
    ll muls = till / min(a, b);
    ans += ((muls) * (muls + 1)) / 2;
    if (n < g - min(a, b)) {
        ll bg = min(a, b) * muls + muls;
        ans += (bg < n) ? (bg - (min(a, b) * muls)) : (n - (min(a, b) * muls));
    }
    return ans;
}

void fun3(ll tn) {
    ll n, a, b;
    fun1(n, a, b);
    printf("%lld\n", fun2(n, a, b));
}

int main() {
    ll t = 1;
    scanf("%lld", &t);
    for (ll tn = 1; tn <= t; tn++) {
        fun3(tn);
    }
    return 0;
}
