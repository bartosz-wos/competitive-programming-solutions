#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int>g[500005];
int st[500005],low[500005], tr;
vector<vector<int>>bccs;
stack<array<int,2>>S;

void dfs(int v, int e){
	st[v]=low[v]=++tr;
	for(const int&i:g[v]){
		if(i==e)continue;
		if(st[i]){
			low[v]=min(low[v],st[i]);
			if(st[i]<st[v])
				S.push({v,i});
		}else{
			S.push({v,i});
			dfs(i,v);
			low[v]=min(low[v],low[i]);
			if(low[i]>=st[v]){
				vector<int>bcc;
				while(1){
					bcc.push_back(S.top()[0]);
					bcc.push_back(S.top()[1]);
					if(S.top()[0]==v and S.top()[1]==i){
						S.pop();
						break;
					}
					S.pop();
				}
				sort(bcc.begin(),bcc.end());
				bcc.erase(unique(bcc.begin(),bcc.end()),bcc.end());
				bccs.push_back(bcc);
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	while(m--){
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i=0;i<n;++i)
		if(!st[i]){
			if(g[i].empty())bccs.push_back({i});
			else dfs(i,-1);
		}
	cout<<bccs.size()<<'\n';
	for(const auto&bcc:bccs){
		cout<<bcc.size()<<' ';
		for(const int&i:bcc)cout<<i<<' ';
		cout<<'\n';
	}
}
