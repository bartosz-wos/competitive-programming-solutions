#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m,k;
 
struct save{
	int a,ra,b,rb;
	save(){}
	save(int a, int ra, int b, int rb):a(a),ra(ra),b(b),rb(rb){}
};
 
struct DSU{
	vector<int>p,r;
	stack<save>S;
	int comps;
	DSU(){}
	DSU(int n){
		p.resize(n+1);
		r.resize(n+1);
		comps=n;
		for(int i=1;i<=n;++i)
			p[i]=i,r[i]=0;
	}
	int find(int x){
		if(p[x]==x)return x;
		return find(p[x]);
	}
	bool unite(int a, int b){
		a=find(a);
		b=find(b);
		if(a==b)return 0;
		--comps;
		if(r[a]>r[b])swap(a,b);
		S.push(save(a,r[a],b,r[b]));
		p[a]=b;
		if(r[a]==r[b])++r[b];
		return 1;
	}
	void roll(){
		if(S.empty())return;
		save x=S.top();
		S.pop();
		++comps;
		p[x.a]=x.a;
		r[x.a]=x.ra;
		p[x.b]=x.b;
		r[x.b]=x.rb;
	}
};
 
struct query{
	int a,b;
	bool united=0;
	query(){}
	query(int a, int b):a(a),b(b){}
};
 
struct QRT{
	vector<vector<query>>t;
	DSU dsu;
	int T;
	QRT(){}
	QRT(int T, int n):T(T){
		dsu=DSU(n+1);
		t.resize(4*T+4);
	}
	void add_to_tree(int ql, int qr, query q, int k, int l, int r){
		if(ql<=l and r<=qr){
			t[k].push_back(q);
			return;
		}
		int mid=(l+r)>>1;
		if(ql<=mid)add_to_tree(ql,qr,q,k<<1,l,mid);
		if(qr>mid)add_to_tree(ql,qr,q,k<<1|1,mid+1,r);
	}
	void add_query(query q, int l, int r){
		add_to_tree(l,r,q,1,1,T);
	}
	void dfs(int v, int l, int r, vector<int>&ans){
		for(query&q:t[v])
			q.united=dsu.unite(q.a,q.b);
		if(l==r)
			ans[l]=dsu.comps;
		else{
			int mid=(l+r)>>1;
			dfs(v<<1,l,mid,ans);
			dfs(v<<1|1,mid+1,r,ans);
		}
		for(query&q:t[v])
			if(q.united)dsu.roll();
	}
	vector<int>solve(){
		vector<int>ans(T+1);
		dfs(1,1,T,ans);
		return ans;
	}
};
 
map<array<int,2>,vector<int>>mp;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>k;
	int T=m+k;
	QRT Tree(T,n);
	for(int i=1;i<=m;++i){
		array<int,2>p;
		cin>>p[0]>>p[1];
		if(p[0]>p[1])swap(p[0],p[1]);
		mp[p].push_back(i);
	}
	for(int i=1;i<=k;++i){
		int t,a,b;
		cin>>t>>a>>b;
		if(a>b)swap(a,b);
		array<int,2>p={a,b};
		mp[p].push_back(m+i);
	}
	for(const auto&i:mp){
		int a=i.first[0];
		int b=i.first[1];
		for(int j=0;j<i.second.size();j+=2){
			if(j+1==i.second.size())Tree.add_query(query(a,b),i.second[j],T);
			else Tree.add_query(query(a,b),i.second[j],i.second[j+1]-1);
		}
	}
	vector<int>ans=Tree.solve();
	for(int i=m;i<=m+k;++i)
		cout<<ans[i]-1<<' ';
}
