#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#endif

#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vb = V<bool>;
using vs = V<string>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x) 
#define len(x) (int)((x).size())
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define lb lower_bound
#define ub upper_bound
template<class T> int lwb(V<T>& a, const T& b) { return lb(all(a),b)-begin(a); }
template<class T> int upb(V<T>& a, const T& b) { return ub(all(a),b)-begin(a); }
template<class T> bool ckmin(T& a, const T& b) { return a > b ? a=b, true : false; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a=b, true : false; }
#define pct __builtin_popcount
#define ctz __builtin_ctz
#define clz __builtin_clz
constexpr int p2(int x) { return (int)1 << x; }
constexpr int bits(int x) { return x == 0 ? 0 : 31-clz(x); } // floor(log2(x)) 

using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res {1};
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x {0} {}
    constexpr MInt(i64 x) : x {norm(x % getMod())} {}
    
    static inline i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v = 69;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};
 
template<>
i64 MInt<0>::Mod = 998244353;
 
constexpr int P = 1000000007;
using Z = MInt<P>;

Z ans=1;

const int LOG=19;
V<vi>up,g;
V<V<array<int,2>>>G;
vi dep,high,clr;
void init_lca(int u,int p){
    for(int v:g[u])if(v!=p){
        up[v][0]=u;
        for(int i=1;i<LOG;i++){
            up[v][i]=up[up[v][i-1]][i-1];
        }
        dep[v]=dep[u]+1;
        init_lca(v,u);
    }
}
int jump(int u,int x){
    for(int i=LOG-1;i>=0;i--)if(x&p2(i)){
        u=up[u][i];
    }
    return u;
}
int get_lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    u=jump(u,dep[u]-dep[v]);
    if(u==v)return u;
    for(int i=LOG-1;i>=0;i--)if(up[u][i]!=up[v][i]){
        u=up[u][i];
        v=up[v][i];
    }
    return up[u][0];
}

int connect(int u,int p){
    for(int v:g[u])if(v!=p){
        int tmp=connect(v,u);
        ckmin(high[u],tmp);
        if(tmp<dep[u]){
            G[u].pb({v,0});
            G[v].pb({u,0});
        }
    }
    return high[u];
}
bool dfs(int u,int c){
    if(clr[u]!=-1)return clr[u]==c;
    clr[u]=c;
    for(auto[v,typ]:G[u])if(!dfs(v,c^typ))return false;
    return true;
}
void solve() {
    int n,q;cin>>n>>q;
    g.resize(n);
    dep.rsz(n);
    up.rsz(n,vi(LOG));
    clr.rsz(n,-1);
    high.rsz(n);
    G.rsz(n);
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;u--;v--;
        g[u].pb(v);g[v].pb(u);
    }
    init_lca(0,-1);
    for(int u=0;u<n;u++)high[u]=dep[u];
    while(q--){
        int u,v;cin>>u>>v;u--;v--;
        int lca=get_lca(u,v);
        ckmin(high[u],dep[lca]);
        ckmin(high[v],dep[lca]);
        if(lca!=u&&lca!=v){
            G[u].pb({v,1});
            G[v].pb({u,1});
        }
    }
    connect(0,-1);
    for(int u=1;u<n;u++)if(clr[u]==-1){
        if(!dfs(u,0))ans=0;
        else ans*=2;
    }
    cout<<ans<<'\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}

