#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
ll dp[1001][1025],n,m;
 
void solve(int x=0, int y=0, int mask=0, int next_mask=0){
	if(x==n)
		return;
	if(y>=m){
		dp[x+1][next_mask]+=dp[x][mask];
		dp[x+1][next_mask]%=mod;
	}
	else{
		ll cmask=1<<y;
		if(mask&cmask)
			solve(x,y+1,mask,next_mask);
		else{
			solve(x,y+1,mask,next_mask|cmask);
			if(y+1<m and !( mask&(cmask<<1) ))
				solve(x,y+2,mask,next_mask);
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>m>>n;
	dp[0][0]=1;
	for(ll i=0;i<n;++i)
		for(ll j=0;j<(1<<m);++j)
			solve(i,0,j,0);
	cout<<dp[n][0];
}
