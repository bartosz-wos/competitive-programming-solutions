#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	ll dp[50]{1};
	for(int i=1;i<=50;++i)
		dp[i]=2*dp[i-1]+(1LL<<(i-1))-1;
	ll ans=0;
	while(n>0){
		ll b=log2(n);
		ans+=dp[b];
		b=1LL<<b;
		ans+=n-b;
		n-=b;
	}
	cout<<ans;
}
