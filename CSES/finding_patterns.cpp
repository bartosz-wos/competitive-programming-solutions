#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll sa[100001];
ll pos[100001];
ll tmp[100001];
ll gap, n;
string s;
 
bool comp(ll x, ll y){
	if(pos[x]!=pos[y])
		return pos[x]<pos[y];
	x+=gap;
	y+=gap;
	return (x<n and y<n)?pos[x]<pos[y]:x>y;
}
 
void suffix(){
	for(ll i=0;i<n;++i)
		sa[i]=i, pos[i]=s[i];
	for(gap=1;;gap<<=1){
		sort(sa,sa+n,comp);
		for(ll i=0;i<n-1;++i)
			tmp[i+1]=tmp[i]+comp(sa[i],sa[i+1]);
		for(ll i=0;i<n;++i)
			pos[sa[i]]=tmp[i];
		if(tmp[n-1]==n-1)
			break;
	}
}
 
ll check(ll m, const string& x){
	ll f=-1;
	ll k=x.size();
	ll j=sa[m];
	if(n-j>=k)
		f=0;
	for(ll i=0;i<min(n-j,k);++i){
		if(s[j+i]<x[i])
			return -1;
		if(s[j+i]>x[i])
			return 1;
	}
	return f;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s;
	n=s.length();
	suffix();
	ll q;
	cin>>q;
	while(q--){
		string x;
		cin>>x;
		ll l=0, r=n-1;
		ll f=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			ll v=check(mid,x);
			if(v==0){
				f=1;
				break;
			}
			else if(v==-1)
				l=mid+1;
			else
				r=mid-1;
		}
		cout<<(f?"YES\n":"NO\n");
	}
}
