#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;

#define fi first
#define se second

constexpr int MAXN=1e5+5;
int n,m,q;
vector<int>g[MAXN];
pi que[MAXN];
int ans[MAXN];
int le[MAXN],ri[MAXN];
vector<int>cand[MAXN];

struct dsu{
    int n;
    vector<int>par;
    dsu(){}
    dsu(int n):n(n){
        par.resize(n+5);
        iota(par.begin(),par.end(),0);
    }
    int find(int x){
        if(par[x]==x)return x;
        return par[x]=find(par[x]);
    }
    void join(int a, int b){
        a=find(a);
        b=find(b);
        if(a==b)return;
        par[b]=a;
    }
}d;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>q;
    for(int i=1;i<=q;++i){
        cin>>que[i].fi>>que[i].se;
        le[i]=1,ri[i]=m;
        ans[i]=-1;
    }
    while(1){
        bool ok=0;
        for(int i=1;i<=q;++i)
            if(le[i]<=ri[i]){
                int mid=(le[i]+ri[i])>>1;
                cand[mid].push_back(i);
                ok=1;
            }
        if(!ok)break;
        d=dsu(n+m);
        for(int mid=1;mid<=m;++mid){
            int x=m-mid+1;
            for(int j=x;j<=n;j+=x)
                d.join(j,x+n);
            for(const int&i:cand[mid]){
                bool flag=d.find(que[i].fi)==d.find(que[i].se);
                if(flag){
                    ans[i]=mid;
                    ri[i]=mid-1;
                }else le[i]=mid+1;
            }
            cand[mid].clear();
        }
    }
    for(int i=1;i<=q;++i)
        cout<<ans[i]<<'\n';
}

