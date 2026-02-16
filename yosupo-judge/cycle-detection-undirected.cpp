#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

int n,m;
vector<pi>g[500005];
bool vis[500005];
int parn[500005];
int pare[500005];

vector<int>path;
vector<int>ids;

void dfs(int v, int e){
        vis[v]=1;
        for(const auto&[u,id]:g[v]){
		if(id==e)continue;
                if(vis[u]){
			path.push_back(v);
			int v2=v;
                        while(v2!=u){
                                ids.push_back(pare[v2]);
				path.push_back(parn[v2]);
                                v2=parn[v2];
                        }
			ids.push_back(id);
                        cout<<ids.size()<<'\n';
			for(const int&i:path)
				cout<<i<<' ';
			cout<<'\n';
                        for(const int&i:ids)
				cout<<i<<' ';
                        exit(0);
                }else if(!vis[u]){
                        pare[u]=id;
			parn[u]=v;
                        dfs(u,id);
                }
        }
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n>>m;
        for(int i=0,a,b;i<m;++i){
                cin>>a>>b;
                g[a].push_back({b,i});
		g[b].push_back({a,i});
        }
        for(int i=0;i<n;++i)
                if(!vis[i])
                        dfs(i,-1);
        cout<<-1<<'\n';
}
