#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll sa[100001];
ll pos[100001];
ll tmp[100001];
ll lcp[100001];
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
 
 
void b_lcp(){
	for(ll i=0,k=0;i<n;++i)
		if(pos[i]!=n-1){
			ll j=sa[pos[i]+1];
			while(s[i+k]==s[j+k])
				++k;
			lcp[pos[i]]=k;
			if(k)
				--k;
		}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s;
	n=s.length();
	suffix();
	b_lcp();
	ll mx=max_element(lcp,lcp+n)-lcp;
	if(lcp[mx]==0){
		cout<<-1;
		exit(0);
	}
	cout<<s.substr(sa[mx],lcp[mx]);
}
