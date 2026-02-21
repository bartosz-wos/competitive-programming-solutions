#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;

#define fi first
#define se second

constexpr int N=3e5+5;

int n,m;

bool vis[N];
set<pi>g[N];
ll cst[N];
ll ret=0;

void dfs(int v, int e, ll c){
        vis[v]=1;
        for(const auto&[i,w]:g[v]){
                if(i==e)continue;
                auto it=g[i].lower_bound({e,0});
                if(it!=g[i].end() and (it->fi)==e)ret=max(ret,c+w+it->se);
                if(!vis[i])dfs(i,v,w);
        }
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        cin>>n>>m;
        while(m--){
                int a,b,c;
                cin>>a>>b>>c;
                g[a].insert({b,c});
                g[b].insert({a,c});
                cst[a]+=c;
                cst[b]+=c;
        }
        for(int i=1;i<=n;++i){
                ret=max(ret,cst[i]);
                if(!vis[i])dfs(i,-1,0);
        }
        cout<<ret<<'\n';
}

