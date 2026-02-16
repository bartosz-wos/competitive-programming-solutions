#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct dsu{
	vector<int>p;
	dsu(int n){
		p.resize(n+1,-1);
	}
	int fd(int x){
		return p[x]<0?x:p[x]=fd(p[x]);
	}
	bool unite(int a, int b){
		a=fd(a);
		b=fd(b);
		if(a==b)return 0;
		if(p[a]>p[b])swap(a,b);
		p[a]+=p[b];
		p[b]=a;
		return 1;
	}
};

struct edge{
	int u,v,c,id;
};

bool cmp(const edge&a, const edge&b){
	return a.c<b.c;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	vector<edge>e(m);
	for(int i=0;i<m;++i){
		cin>>e[i].u>>e[i].v>>e[i].c;
		e[i].id=i;
	}
	ll tot=0;
	vector<int>res;
	dsu g(n);
	sort(e.begin(),e.end(),cmp);
	for(const auto&i:e)
		if(g.unite(i.u,i.v)){
			tot+=i.c;
			res.push_back(i.id);
		}
	cout<<tot<<'\n';
	sort(res.begin(),res.end());
	for(const int&i:res)
		cout<<i<<' ';
}
