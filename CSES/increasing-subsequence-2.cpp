#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
 
ll n;
ll a[200001];
set<ll>S;
 
ll bit[200001];
map<int,int>mp;
 
void upd(int i, ll x){
	for(;i<=n;i+=i&-i)
		bit[i]+=x,bit[i]%=mod;
}
 
ll qry(int i){
	ll res=0;
	for(;i;i-=i&-i)
		res+=bit[i], res%=mod;
	return res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>a[i],S.insert(a[i]);
	int ct=0;
	for(const ll& i:S)
		mp[i]=++ct;
	ll ans=0;
	for(int i=0;i<n;++i){
		int x=qry(mp[a[i]]-1)+1;
		ans+=x;
		ans%=mod;
		upd(mp[a[i]],x);
	}
	cout<<ans;
}
