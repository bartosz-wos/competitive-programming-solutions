#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;
constexpr int MAXN=5e5+1;
int n,m,nxt[MAXN],cyc;
bool vis[MAXN],trav[MAXN];
vector<ar>g[MAXN];
vector<int>res;

void dfs(int v){
        vis[v]=1;
        while(nxt[v]<g[v].size()){
                auto i=g[v][nxt[v]++];
                if(!trav[i[1]]){
                        trav[i[1]]=1;
                        if(vis[i[0]]){
                                res.push_back(v);
                                cyc=i[0];
                                return;
                        }
                        dfs(i[0]);
                        res.push_back(v);
                        if(cyc==v){
                                for(const int&i:res){
                                        cout<<i<<' ';
                                        vis[i]=0;
                                }
                                res.clear();
                                cout<<'\n';
                                cyc=0;
                                vis[v]=1;
                        }
                        else if(cyc)return;
                }
        }
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,m;
        cin>>n>>m;
        for(int i=0,a,b;i<m;++i){
                cin>>a>>b;
                g[a].push_back({b,i});
                g[b].push_back({a,i});
        }
        for(int i=1;i<=n;++i)
                if(nxt[i]<g[i].size())dfs(i);
}

