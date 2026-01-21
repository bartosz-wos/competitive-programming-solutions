#include"stations.h"
#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=1005;
int a[N];
vector<int>g[N];
ll tr=0;

void dfs(int v, int e, int d){
    if(d%2==0)a[v]=tr++;
    for(const int&i:g[v])
        if(i!=e)dfs(i,v,d+1);
    if(d&1)a[v]=tr++;
}

vector<int>label(int n, int k, vector<int>u, vector<int>v){
    for(int i=0;i<n;++i)g[i].clear();
    for(int i=0;i<u.size();++i){
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }
    tr=0;
    dfs(0,-1,0);
    vector<int>ret;
    for(int i=0;i<n;++i)ret.push_back(a[i]);
    return ret;
}

int find_next_station(int s, int t, vector<int>c){
    if(s>c[0]){
        if(s<t or t<c[0])return c[0];
        int mx=0;
        for(int i=0;i<c.size();++i)
            if(t>=c[i])
                mx=max(mx,c[i]);
        return mx;
    }
    if(c.back()<t or t<s)return c.back();
    int mn=1e9;
    for(int i=0;i<c.size();++i)
        if(t<=c[i])
            mn=min(mn,c[i]);
    return mn;
}



