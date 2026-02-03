#include"nile.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()

constexpr int MAXN=1e5+5;
constexpr int MAXT=3e5+5;

struct mtrx{
    ll A[3][3];
    mtrx(){
        memset(A,0x3f,sizeof A);
        A[0][0]=A[1][1]=A[2][2]=0;
    }
    mtrx operator+(const mtrx&m){
        mtrx ret;
        memset(ret.A,0x3f,sizeof ret.A);
        for(int i=0;i<3;++i)
            for(int j=0;j<3;++j)
                for(int k=0;k<3;++k)
                    ret.A[i][k]=min(A[i][j]+m.A[j][k],ret.A[i][k]);
        return ret;
    }
}M[MAXN];

struct segtree{
    int lim;
    mtrx tree[MAXT];
    void init(int n){
        for(lim=1;lim<=n;lim<<=1);
        for(int i=0;i<n;++i)
            tree[i+lim]=M[i];
        for(int i=lim-1;i;--i)
            tree[i]=tree[i<<1]+tree[i<<1|1];
    }
    void upd(int x, mtrx v){
        x+=lim;
        tree[x]=v;
        while(x>1){
            x>>=1;
            tree[x]=tree[x<<1]+tree[x<<1|1];
        }
    }
}seg;

vector<ll>calculate_costs(vector<int>W,vector<int>A,vector<int>B,vector<int>E){
    int n=sz(W);
    vector<array<ll,3>>a(n);
    for(int i=0;i<n;++i)
        a[i]={W[i],A[i],B[i]};
    sort(all(a));
    vector<array<int,3>>events;
    for(int i=1;i<n;++i){
        events.push_back({a[i][0]-a[i-1][0],i-1,i});
        if(i>1)events.push_back({a[i][0]-a[i-2][0],i-2,i});
    }
    sort(all(events));
    for(int i=0;i<n;++i){
        memset(M[i].A,0x3f,sizeof M[i].A);
        M[i].A[0][0]=a[i][1];
        M[i].A[1][0]=M[i].A[2][1]=0;
    }
    vector<pi>ans;
    seg.init(n);
    ans.push_back({0,seg.tree[1].A[0][0]});
    for(auto&[v,l,r]:events){
        if(r-l==2)
            M[l].A[0][2]=a[l][2]+a[r][2]+a[l+1][1];
        else
            M[l].A[0][1]=a[l][2]+a[r][2];
        seg.upd(l,M[l]);
        ans.push_back({v,seg.tree[1].A[0][0]});
    }
    vector<ll>dap(sz(E));
    vector<pi>qr;
    for(int i=0;i<sz(E);++i)
        qr.push_back({E[i],i});
    sort(all(qr));
    int j=0;
    for(auto&[k,idx]:qr){
        while(j<sz(ans) and ans[j][0]<=k)++j;
        dap[idx]=ans[j-1][1];
    }
    return dap;
}

