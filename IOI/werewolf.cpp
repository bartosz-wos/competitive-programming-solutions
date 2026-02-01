#include<bits/stdc++.h>
#include"werewolf.h"
using namespace std;

constexpr int N=2e5+5;
vector<int>sons[N<<1];
set<int>nodes[N];
int n;
vector<int>ql[N],qr[N];
vector<int>g[N];
int nod_inter[N];
int st[N<<1],en[N<<1];

struct DSU{
    int par[N<<1];
    int id=0;
    void init(){
        for(int i=0;i<2*n;++i)par[i]=i;
        id=n-1;
    }
    int root(int x){
        if(par[x]==x)return x;
        return par[x]=root(par[x]);
    }
    void unite1(int u, int v){
        u=root(u);
        v=root(v);
        if(u==v)return;
        ++id;
        sons[id].push_back(u);
        sons[id].push_back(v);
        par[u]=par[v]=id;
    }
    void unite2(int u, int v){
        u=root(u);
        v=root(v);
        if(u==v)return;
        if(nodes[u].size()<nodes[v].size())swap(u,v);
        par[v]=u;
        for(auto it:nodes[v])nodes[u].insert(it);
        nodes[v].clear();
    }
}dsu;

void dfs(int v){
    static int tr=0;
    st[v]=tr;
    for(const int&i:sons[v])
        dfs(i);
    if(sons[v].empty())++tr;
    en[v]=tr-1;
}

vector<int>check_validity(int N,vector<int>X,vector<int>Y,vector<int>S,vector<int>E,vector<int>L,vector<int>R){
    int q=S.size();
    int m=X.size();
    n=N;
    for(int i=0;i<q;++i){
        ql[L[i]].push_back(i);
        qr[R[i]].push_back(i);
    }
    for(int i=0;i<m;++i){
        g[X[i]].push_back(Y[i]);
        g[Y[i]].push_back(X[i]);
    }
    dsu.init();
    for(int i=n-1;i>=0;--i){
        for(auto vec:g[i])
            if(vec>i)
                dsu.unite1(i,vec);
        for(auto qry:ql[i])
            nod_inter[qry]=dsu.root(S[qry]);
    }
    dfs(dsu.id);
    dsu.init();
    for(int i=0;i<n;++i)nodes[i].insert(st[i]);
    vector<int>ans(q);
    for(int i=0;i<n;++i){
        for(auto vec:g[i])
            if(vec<i)dsu.unite2(i,vec);
        for(auto qry:qr[i]){
            int pos=E[qry];
            int rt=dsu.root(pos);
            int intv=nod_inter[qry];
            auto it=nodes[rt].lower_bound(st[intv]);
            if(it!=nodes[rt].end() and *it<=en[intv])ans[qry]=1;
            else ans[qry]=0;
        }
    }
    return ans;
}
