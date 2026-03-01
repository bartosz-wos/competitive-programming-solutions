#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll dp[1000005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	dp[0]=1%m;
	for(int i=1;i<=n;++i){
		if(i==1)dp[i]=0;
		else dp[i]=(1ll*i-1ll)*(dp[i-1]+dp[i-2])%m;
		cout<<dp[i]<<' ';
	}
	cout<<'\n';
}
