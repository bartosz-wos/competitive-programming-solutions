#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
tree_order_statistics_node_update>;
#define cut4(a,b,c,d,e,...) e
#define rep1(n) for(int i=0;i<(n);++i)
#define rep2(i,n) for(int i=0;i<(n);++i)
#define rep3(i,a,b) for(int i=(a);i<(b);++i)
#define rep4(i,a,b,c) for(int i=(a);i<(b);i+=(c))
#define rev1(n) for(int i=(n)-1;i>=0;--i)
#define rev2(i,n) for(int i=(n)-1;i>=0;--i)
#define rev3(i,a,b) for(int i=(a)-1;i>=(b);--i)
#define rev4(i,a,b,c) for(int i=(a)-1;i>=(b);i-=(c))
#define rep(...) cut4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rev(...) cut4(__VA_ARGS__,rev4,rev3,rev2,rev1)(__VA_ARGS__)
#define each(a, x) for(auto& a:x)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define over(x) {cout<<(x)<<'\n';return;}
#define chmin(a,b) a=min(a,b)
#define chmax(a,b) a=max(a,b)
#define pb push_back
#define f first
#define s second
typedef long long ll;
typedef long double db;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
ll rng() { return uniform_int_distribution<ll>(0, INT64_MAX)(gen); }
/*const db PI = atan(1)*4;*/
/*const ll mod = 1e9+7;*/
const int mod=30013;
const int mx=4e5+5;
pi t[4*mx];
pi pull(pi l, pi r){
    if(l.f==r.f)return {l.f,(l.s+r.s)%mod};
    return l.f>r.f?l:r;
}
void update(int k, pi x, int v, int tl, int tr){
    if(tl==tr) t[v]=x;
    else {
        int tm=(tl+tr)/2;
        if(k<=tm)update(k,x,v*2,tl,tm);
        else update(k,x,v*2+1,tm+1,tr);
        t[v]=pull(t[v*2],t[v*2+1]);
    }
}
pi query(int l, int r, int v, int tl, int tr){
    if(r<tl||tr<l)return pi{0,0};
    if(l<=tl&&tr<=r)return t[v];
    int tm=(tl+tr)/2;
    return pull(query(l,r,v*2,tl,tm),query(l,r,v*2+1,tm+1,tr));
}
void solve(int){
    int n;
    cin>>n;
    vector<array<int, 4>> a(n);
    vi vals(4*n);
    rep(n){
        rep(j,4)cin>>a[i][j], vals[i*4+j]=a[i][j];
    }
    sort(all(vals));
    vals.erase(unique(all(vals)),vals.end());
    rep(n) rep(j,4)a[i][j]=lower_bound(all(vals),a[i][j])-vals.begin();
    vpi ans(n);
    vpi ord(n);
    sort(all(a),[&](const auto& p, const auto& q){
        return p[0]<q[0];
    });
    rep(n)ord[i]={a[i][1], i};
    sort(all(ord));
    int j=0;
    rep(n){
        while(j<n&&ord[j].f<a[i][0]){
            update(a[ord[j].s][3],ans[ord[j].s],1,0,mx-1);
            j++;
        }
        ans[i]=pull(query(0,a[i][2]-1,1,0,mx-1), pi{0,1});
        ans[i].f++;
        /*cout<<ans[i].f<<' '<<ans[i].s<<'\n';*/
    }
    int m=0;
    rep(n)chmax(m,ans[i].f);
    int cnt=0;
    rep(n)if(ans[i].f==m)cnt=(cnt+ans[i].s)%mod;
    cout<<m<<' '<<cnt<<'\n';
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int tc=1;
    /*cin>>tc;*/
    rep(tc) solve(i);
    return 0;
}

