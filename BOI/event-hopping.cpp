#include<bits/stdc++.h>
#define pb push_back
#define pf push_front
#define mp make_pair
#define F first
#define S second
#define ff first
#define ss second
#define str string
#define ll long long
#define ull unsigned ll
#define ld long double
#define pll pair<ll,ll>
#define plll pair<pll,ll>
#define pllll pair<pll,pll>
#define pii pair<int,int>
#define pld pair<ld,ld>
#define vl vector<ll>
#define vll vector<pll>
#define vlll vector<plll>
#define vllll vector<pllll>
#define vb vector<bool>
#define vi vector<int>
#define vii vector<pii>
#define sz(x) (ll)(x).size()
#define fr front()
#define tp top()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define bk back();
#pragma GCC target( "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("Ofast,unroll-loops,fast-math,O3")
using namespace std;
const ld pi=acos(-1.0);
const ll e5=1e5;
const ll e6=1e6;
const ll e9=1e9;
const ll inf=1e18;
const ll mod=1e9+7;
const ll mod2=998244353;
const ll MOD=106710087877475399;
const ll N=2e5+10;
const ll M=50+10;
const ld eps=1e-9;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll bpm(ll x,ll y,ll m){if(y==0)return 1%m;ll p=bpm(x,y/2,m);
if(y%2==0)return p*p%m;else return p*p%m*x%m;}
ll bp(ll x,ll y){if(y==0)return 1;ll p=bp(x,y/2);
if(y%2==0)return p*p;else return p*p*x;}
ll n,q,s[N],e[N];
pll t[N*8],up[N][17];
void bld(ll v,ll l,ll r){
    t[v]={inf,0};
    if(l==r) return;
    ll m=(l+r)/2;
    bld(v*2,l,m);
    bld(v*2+1,m+1,r);
}
void upd(ll v,ll l,ll r,ll i,ll x,ll y){
    if(l==r){
        t[v]=min(t[v],{x,y});
        return;
    }
    ll m=(l+r)/2;
    if(i<=m) upd(v*2,l,m,i,x,y);
    else upd(v*2+1,m+1,r,i,x,y);
    t[v]=min(t[v*2],t[v*2+1]);
}
pll get(ll v,ll l,ll r,ll ql,ll qr){
    if(qr<l||r<ql) return {inf,0};
    if(ql<=l&&r<=qr) return t[v];
    ll m=(l+r)/2;
    return min(get(v*2,l,m,ql,qr), get(v*2+1,m+1,r,ql,qr));
}
void solve(){
    cin>>n>>q;
    vl v;
    for(ll i=1;i<=n;i++){
        cin>>s[i]>>e[i];
        v.pb(s[i]);
        v.pb(e[i]);
    }
    sort(all(v));
    v.erase(unique(all(v)),v.end());
    bld(1,1,n*2);
    for(ll i=1;i<=n;i++){
        s[i]=lower_bound(all(v),s[i])-v.begin()+1;
        e[i]=lower_bound(all(v),e[i])-v.begin()+1;
        upd(1,1,n*2,e[i],s[i],i);
    }
    for(ll i=1;i<=n;i++){
        up[i][0]=get(1,1,n*2,s[i],e[i]);
    }
    for(ll j=1;j<17;j++){
        for(ll i=1;i<=n;i++){
            up[i][j]=up[up[i][j-1].S][j-1];
        }
    }
    while(q--){
        ll a,b; cin>>a>>b;
        if(e[a]>e[b]){ cout<<"impossible\n"; continue;}
        if(a==b){ cout<<"0\n"; continue;}
        if(s[b]<=e[a]&&e[a]<=e[b]){ cout<<"1\n"; continue;}
        ll ans=inf,s=0;
        for(ll j=16;j>=0;j--){
            pll p=up[b][j];
            if(p.F<=e[a]) ans=min(ans,s+(1<<j));
            else s+=(1<<j), b=p.S;
        }
        if(ans==inf) cout<<"impossible\n";
        else cout<<ans+1<<'\n';
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false);  cin.tie(NULL);
    int test=1;
    //cin>>test;
    for(int i=1;i<=test;i++){
        solve();
        cout<<'\n';
    }
    return 0;
}
