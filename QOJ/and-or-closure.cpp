#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll= long long ;

int main(){
	cin.tie(0)->sync_with_stdio(0);
	ll n;
	cin>>n;
	vector<ll>A(n),on(40),ze(40);
	vector<ll>and_mask(40,(1ll<<40)-1),or_mask(40);
	unordered_map<ll,ll>mp[40];
	for(ll i=0;i<n;++i){
		ll x;
		cin>>x;
		for(ll j=0;j<40;++j){
			if(x>>j&1)and_mask[j]&=x,on[j]=1;
			else or_mask[j]|=x,ze[j]=1;
		}
	}
	auto dfs=[&](auto self ,ll x,ll tag)->ll{
		if(x<0)return 1;
		if(mp[x].count(tag))return mp[x][tag];
		if(tag>>x&1){
			ll res=0;
			if(ze[x])res+=self(self ,x-1,or_mask[x]&tag);
			if(on[x])res+=self(self ,x-1,~and_mask[x]&tag);
			return mp[x][tag]=res;
		}
		return self(self ,x-1,tag);
	};
	cout<<dfs(dfs,39,(1ll<<40)-1)<<endl;
}
