#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
vector<int>v;
int prime[205];
 
ll dp[20][205];
 
void sieve(){
	prime[0]=prime[1]=1;
	for(int i=2;i*i<=200;++i)
		if(!prime[i])
			for(int j=i*i;j<=200;j+=i)
				prime[j]=1;
}
 
ll get(int pos, int sum, bool f){
	if(pos==v.size())return !prime[sum];
	ll&ret=dp[pos][sum];
	if(f and ret!=-1)return ret;
	ll ans=0;
	int lim=9;
	if(!f)lim=v[pos];
	for(int i=0;i<=lim;++i)
		ans+=get(pos+1,sum+i,f or i!=v[pos]);
	return f?ret=ans:ans;
}
 
ll solve(ll x){
	if(x<=1)return 0;
	v.clear();
	while(x){
		v.push_back(x%10);
		x/=10;
	}
	reverse(v.begin(),v.end());
	memset(dp,-1,sizeof dp);
	return get(0,0,0);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	sieve();
	ll a,b;
	int t;
	cin>>t;
	while(t--){
		cin>>a>>b;
		cout<<solve(b)-solve(a-1)<<'\n';
	}
}
