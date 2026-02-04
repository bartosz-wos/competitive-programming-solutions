#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define plx pair<ll,int>
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(),x.end()
#define vi vector<int>
#define vvi vector<vi>
#define pp pair<ll,int>
#define ub(x,i) upper_bound(all(x),i)-x.begin()
#define lb(x,i) lower_bound(all(x),i)-x.begin()
#define t3 tuple<int,int,int>
using namespace std;
const int mxn=4e5+5;
vector<pll>v;
multiset<pll>ms;
int id[mxn];
struct node{
    ll mxl,mxr,mx,tt;
    node operator+(node b){
        return node{max(mxl,tt+b.mxl),max(b.mxr,b.tt+mxr),max({mx,b.mx,mxr+b.mxl}),tt+b.tt};
    }
}t[4*mxn];

void update(int i,int l,int r,int id,ll amt){
    if(r<id||l>id)return;
    if(l==r)return void(t[i]=node{max(1ll*0,amt),max(1ll*0,amt),max(1ll*0,amt),amt});
    int m=(l+r)>>1;
    update(2*i,l,m,id,amt);update(2*i+1,m+1,r,id,amt);
    t[i]=t[2*i]+t[2*i+1];
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    ll n,m,d;cin>>n>>m>>d;ll a[n+m];
    for(int i=0;i<n;i++){
        cin>>a[i];v.pb({a[i],i});
    }
    for(int i=0;i<m;i++){
        cin>>a[i+n];v.pb({a[i+n],i+n});
    }sort(all(v));
    for(int i=0;i<n+m;i++)id[v[i].s]=i+1;
    for(int i=0;i<n;i++){
        ms.insert({a[i],i});
        auto it=ms.lower_bound({a[i],i});
        if(it!=ms.begin()){
            update(1,1,m+n,id[i],d-(a[i]-prev(it)->f));
        }
        if(it!=(--ms.end())){
            update(1,1,m+n,id[next(it)->s],d-(next(it)->f-a[i]));
        }
    }
    for(int i=0;i<m;i++){
        ms.insert({a[i+n],i+n});
        auto it=ms.lower_bound({a[i+n],i+n});
        if(it!=ms.begin()){
            update(1,1,m+n,id[i+n],d-(a[i+n]-prev(it)->f));
        }
        if(it!=(--ms.end())){
            update(1,1,m+n,id[next(it)->s],d-(next(it)->f-a[i+n]));
        }
        ll rs=t[1].mx;
        if(rs&1)cout<<rs/2<<".5 ";
        else cout<<rs/2<<" ";
    }
}
