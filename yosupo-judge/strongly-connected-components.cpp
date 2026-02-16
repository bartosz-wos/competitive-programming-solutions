#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m;
bool vis[500005];
vector<int>g[500005],rg[500005];
vector<int>ord,comp;

void dfs(int v){
        vis[v]=1;
        for(const int&i:g[v])
                if(!vis[i])
                        dfs(i);
        ord.push_back(v);
}

void dfs2(int v){
        vis[v]=1;
        comp.push_back(v);
        for(const int&i:rg[v])
                if(!vis[i])
                        dfs2(i);
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n>>m;
        while(m--){
                int a,b;
                cin>>a>>b;
                g[a].push_back(b);
                rg[b].push_back(a);
        }
        for(int i=0;i<n;++i)
                if(!vis[i])
                        dfs(i);
        reverse(ord.begin(),ord.end());
        memset(vis,0,sizeof vis);
        vector<vector<int>>comps;
        for(const int&i:ord)
                if(!vis[i]){
                        dfs2(i);
                        comps.push_back(comp);
                        comp.clear();
                }
        cout<<comps.size()<<'\n';
        for(const auto&c:comps){
                cout<<c.size()<<' ';
                for(const int&i:c)cout<<i<<' ';
                cout<<'\n';
        }
}
