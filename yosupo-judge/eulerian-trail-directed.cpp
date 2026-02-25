#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

void solve(){
	int n,m;
	cin>>n>>m;
	vector<vector<pi>>g(n);
	vector<int>indeg(n),outdeg(n);
	for(int i=0,a,b;i<m;++i){
		cin>>a>>b;
		g[a].push_back({b,i});
		++indeg[b];
		++outdeg[a];
	}
	int st=-1,cnt_st=0,cnt_en=0;
	bool ok=1;
	for(int i=0;i<n;++i){
		if(outdeg[i]-indeg[i]==1)++cnt_st,st=i;
		else if(indeg[i]-outdeg[i]==1)++cnt_en;
		else if(indeg[i]!=outdeg[i])ok=0;
	}
	if(cnt_st>1 or cnt_en>1)ok=0;
	if(!ok){
		cout<<"No\n";
		return;
	}
	if(!~st){
		for(int i=0;i<n;++i)
			if(outdeg[i]){
				st=i;
				break;
			}
		if(!~st)st=0;
	}
	vector<int>pv,pe;
	stack<pi>s;
	s.push({st,-1});
	while(!s.empty()){
		int v=s.top()[0];
		if(!g[v].empty()){
			auto[i,id]=g[v].back();
			g[v].pop_back();
			s.push({i,id});
		}else{
			int id=s.top()[1];
			s.pop();
			pv.push_back(v);
			if(~id)pe.push_back(id);
		}
	}
	if(pv.size()!=m+1){
		cout<<"No\n";
		return;
	}
	cout<<"Yes\n";
	reverse(pv.begin(),pv.end());
	reverse(pe.begin(),pe.end());
	for(const int&i:pv)cout<<i<<' ';
	cout<<'\n';
	for(const int&i:pe)cout<<i<<' ';
	cout<<'\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
}
