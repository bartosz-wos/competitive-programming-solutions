#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=210,M=2010,Lim=2e18+1;
int n,m,s,t;
int f[N][N];

vector<pair<int,char>>eg[N],ge[N];

struct Item{
	int w,u,v;
	bool operator>(const Item&t)const{
		return w>t.w;
	}
};
bool match(char u,char v){
	if(u=='(')return v==')';
	if(u=='[')return v==']';
	if(u=='{')return v=='}';
	if(u=='<')return v=='>';
	return false;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m>>s>>t;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j)f[i][j]=Lim;
	
	while(m--){
		int u,v;char ch;
		cin>>u>>v>>ch;
		eg[u].push_back({v,ch});
		ge[v].push_back({u,ch});
	}
	priority_queue<Item,vector<Item>,greater<Item>>q;
	for(int i=1;i<=n;i++)q.push({0,i,i});
	
	while(q.size()){
		int w=q.top().w,u=q.top().u,v=q.top().v;q.pop();
		if(w!=f[u][v])continue;
		for(auto pu:ge[u])
			for(auto pv:eg[v])
				if(match(pu.second,pv.second)){
					if(w+2<f[pu.first][pv.first]){
						f[pu.first][pv.first]=w+2;
						q.push({w+2,pu.first,pv.first});
					}
				}
		for(int z=1;z<=n;z++){
				if(f[u][v]+f[v][z]<f[u][z]){
					f[u][z]=f[u][v]+f[v][z];
					q.push({f[u][z],u,z});
				}
				if(f[z][u]+f[u][v]<f[z][v]){
					f[z][v]=f[z][u]+f[u][v];
					q.push({f[z][v],z,v});
				}
		}
	}
	if(f[s][t]==Lim){
		cout<<-1;
	}
	else{
		cout<<f[s][t];
	}
}
