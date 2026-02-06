#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int nx=8e4+5;
constexpr int mx=240105;

int n,m,a[nx],b[nx],c[nx],d[nx],x[nx],y[nx],cl[nx],tx,ty,tc;
int pa[nx],in[nx],out[nx],t,id[nx],sz[nx],cnt[nx],ans[nx],res;
map<int,int>mpx,mpy,mpc;
vector<int>add[mx],rem[mx],pts[mx],g[mx],s[mx];

struct fenwick{
    int d[mx];
    void add(int i, int x){
        for(;i<mx;i+=i&-i)
            d[i]+=x;
    }
    int query(int i){
        int res=0;
        while(i){
            res+=d[i];
            i-=i&-i;
        }
        return res;
    }
}f;

void dfs(int u){
    in[u]=++t;
    id[t]=u;
    sz[u]=1;
    sz[u]+=s[u].size();
    for(auto v:g[u])dfs(v),sz[u]+=sz[v];
    out[u]=t;
}

void sack(int u, bool del){
    pair<int,int>hv={-1,-1};
    for(auto v:g[u])hv=max(hv,{sz[v],v});
    for(auto v:g[u])if(v!=hv.second)sack(v,1);
    if(hv.second!=-1)sack(hv.second,0);
    for(auto tmp:s[u])if(cnt[tmp]++==0)++res;
    for(auto v:g[u])
        if(v!=hv.second)
            for(int i=in[v];i<=out[v];++i)
                for(auto tmp:s[id[i]])
                    if(cnt[tmp]++==0)++res;
    ans[u]=res;
    if(del)
        for(int i=in[u];i<=out[u];++i)
            for(auto tmp:s[id[i]])
                if(cnt[tmp]--==1)--res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i)cin>>a[i]>>b[i]>>c[i]>>d[i],mpx[a[i]]=0,mpy[b[i]]=0,mpx[c[i]]=0,mpy[d[i]]=0;
    for(int i=1;i<=m;++i)cin>>x[i]>>y[i]>>cl[i],mpx[x[i]]=0,mpy[y[i]]=0,mpc[cl[i]]=0;
    for(auto&[k,idx]:mpx)idx=++tx;
    for(auto&[k,idx]:mpy)idx=++ty;
    for(auto&[k,idx]:mpc)idx=++tc;
    for(int i=1;i<=n;++i){
        a[i]=mpx[a[i]];
        b[i]=mpy[b[i]];
        c[i]=mpx[c[i]];
        d[i]=mpy[d[i]];
        add[a[i]].push_back(i);
        rem[c[i]].push_back(i);
    }
    for(int i=1;i<=m;++i){
        x[i]=mpx[x[i]];
        y[i]=mpy[y[i]];
        cl[i]=mpc[cl[i]];
        pts[x[i]].push_back(i);
    }
    for(int i=1;i<mx;++i){
        for(auto&idx:add[i]){
            pa[idx]=f.query(b[idx]);
            g[pa[idx]].push_back(idx);
            f.add(b[idx],idx-pa[idx]);
            f.add(d[idx]+1,pa[idx]-idx);
        }
        for(auto idx:pts[i])
            s[f.query(y[idx])].push_back(cl[idx]);
        for(auto idx:rem[i])
            f.add(b[idx],pa[idx]-idx),f.add(d[idx]+1,idx-pa[idx]);
    }
    dfs(0);
    sack(0,0);
    for(int i=1;i<=n;++i)
        cout<<ans[i]<<'\n';
}
