#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll=long long;
using pi=array<int,2>;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

pi op(pi a,pi b) {
	if(a[0]==b[0])return {a[0],a[1]+b[1]};
	if(a[1]>b[1])return {a[0],a[1]-b[1]};
	if(a[1]<b[1])return {b[0],b[1]-a[1]};
	return {0, 0};
}

pi e(){return {0,0};}

template <class T, T (*op)(T, T), T(*e)()>
struct segtree{
	vector<T>d;
	int n;
	T a,b;
	segtree(int n=0):segtree(vector<T>(n, e())){}
	segtree(const vector<T>& v):n((int)v.size()){ 
		d.assign(n<<1,e());
		for(int i=0;i<n;++i)d[n+i]=v[i];
		for(int i=n-1;i>=1;--i)d[i]=op(d[i<<1],d[i<<1|1]);
	}
	void set(int p, T x){ 
		d[p+=n]=x;
		for(p>>=1;p;p>>=1)d[p]=op(d[p<<1],d[p<<1|1]); 
	}
	T operator[](int p){return d[p+n];}
	T operator()(int l, int r){
		a=e(),b=e();
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){ 
			if(l&1)a=op(a,d[l++]); 
			if(r&1)b=op(d[--r],b); 
		}
		return op(a,b);
	}
};

struct query{
	int t,a,b,c;
};

ordered_set occ[1000005];

int a[500005];
query qr[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	vector<int>vals;
	for(int i=0;i<n;++i){
		cin>>a[i];
		vals.push_back(a[i]);
	}
	for(int i=0;i<q;++i){
		cin>>qr[i].t;
		if(!qr[i].t){
			cin>>qr[i].a>>qr[i].b;
			vals.push_back(qr[i].b);
		}else cin>>qr[i].a>>qr[i].b;
	}
	sort(vals.begin(),vals.end());
	vals.erase(unique(vals.begin(),vals.end()),vals.end());
	auto get_id=[&](int x){
	       	return lower_bound(vals.begin(),vals.end(),x)-vals.begin(); 
	};

	vector<pi>init(n);
	for (int i=0;i<n;++i){
		a[i]=get_id(a[i]);
		occ[a[i]].insert(i);
		init[i]={a[i],1};
	}
	segtree<pi,op,e>st(init);
	for(int i=0;i<q;++i){
		if(!qr[i].t){
			int x=get_id(qr[i].b);
			occ[a[qr[i].a]].erase(qr[i].a);
			a[qr[i].a]=x;
			occ[a[qr[i].a]].insert(qr[i].a);
			st.set(qr[i].a,{a[qr[i].a],1});
		}else{
			pi ret=st(qr[i].a,qr[i].b);
			int f=occ[ret[0]].order_of_key(qr[i].b)-occ[ret[0]].order_of_key(qr[i].a);
			if ((f<<1)>qr[i].b-qr[i].a)cout<<vals[ret[0]]<<'\n';
			else cout<<-1<<'\n';
		}
	}

}
