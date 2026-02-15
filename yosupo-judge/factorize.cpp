#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

ll gcd(ll _a, ll _b) {
    ull a = abs(_a), b = abs(_b);
    if (a == 0) return b;
    if (b == 0) return a;
    int shift = bsf(a|b);
    a >>= bsf(a);
    do {
        b >>= bsf(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return (a << shift);
}

template<class T, class U>
T pow_mod(T x, U n, T md) {
    T r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n <= a) break;
        ll t = d;
        ll y = pow_mod<__int128_t>(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = __int128_t(y) * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

ll pollard_single(ll n) {
    if(is_prime(n))return n;
    if (n % 2 == 0) return 2;
    ll st = 0;
    auto f = [&](ll x) { return (__int128_t(x) * x + st) % n; };
    while (true) {
        st++;
        ll x = f(st), y = f(x);
        while (true) {
            ll p = gcd(abs(y-x), n);
            if (p == 0 || p == n) break;
            if (p != 1) return p;
            x = f(x);
            y = f(f(y));
        }
    }
}

int s[10000005];
vector<int>pr;

void init(){
        for(int i=2;i<=(ll)1e7;++i){
                if(!s[i]){
                        s[i]=i;
                        pr.push_back(i);
                }
                for(int j=0;pr[j]*i<=(ll)1e7;++j){
                        s[pr[j]*i]=pr[j];
                        if(pr[j]==s[i])break;
                }
        }
}

V<ll>fact(ll n){
        V<ll>ret;
        while(s[n]!=n and n!=1){
                ret.push_back(s[n]);
                n/=s[n];
        }
        if(n!=1)ret.push_back(n);
        return ret;
}

V<ll> pollard(ll n) {
    if (n == 1) return {};
    if(n<=(ll)1e7)return fact(n);
    ll x = pollard_single(n);
    if (x == n) return {x};
    V<ll> le = pollard(x);
    V<ll> ri = pollard(n / x);
    le.insert(le.end(), ri.begin(), ri.end());
    return le;
}

int main() {
    init();
    int q;
    scanf("%d", &q);
    map<ll, V<ll>> cache;
    for (int i = 0; i < q; i++) {
        ll a;
        scanf("%lld", &a);
        if (!cache.count(a)) {
            auto v = pollard(a);
            sort(v.begin(), v.end());
            cache[a] = v;
        }
        auto v = cache[a];
        printf("%d", int(v.size()));
        for (auto d: v) printf(" %lld", d);
        printf("\n");
    }
    return 0;
}

