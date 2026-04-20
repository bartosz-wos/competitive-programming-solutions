#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pt=complex<ll>;
constexpr int mxn=1e6;
 
namespace Con{
	vector<pt>line(mxn<<2,{0,(ll)1e18});
 
	ll dot(pt a, pt b){
		return (conj(a)*b).real();
	}
 
	ll f(pt a, ll x){
		return dot(a,{x,1});
	}
 
	void add(pt nw, int k=1, int l=0, int r=mxn){
		int mid=(l+r)>>1;
		bool lef=f(nw,l)<f(line[k],l);
		bool m=f(nw,mid)<f(line[k],mid);
		if(m)
			swap(line[k],nw);
		if(r-l==1)
			return;
		else if(lef!=m)
			add(nw,k<<1,l,mid);
		else
			add(nw,k<<1|1,mid,r);
	}
 
	ll get(int x, int k=1, int l=0, int r=mxn){
		int mid=(l+r)>>1;
		if(r-l==1)
			return f(line[k],x);
		else if(x<mid)
			return min(f(line[k],x),get(x,k<<1,l,mid));
		else
			return min(f(line[k],x),get(x,k<<1|1,mid,r));
	}
};
 
int n,x;
int s[200001];
int f[200001];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>x;
	for(int i=1;i<=n;++i)
		cin>>s[i];
	for(int i=1;i<=n;++i)
		cin>>f[i];
	Con::add({x,0});
	for(int i=1;i<n;++i){
		ll res=Con::get(s[i]);
		Con::add({f[i],res});
	}
	cout<<Con::get(s[n]);
}
