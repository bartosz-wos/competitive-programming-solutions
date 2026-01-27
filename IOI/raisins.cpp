#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int t[51][51];
ll p[51][51];
ll dp[52][52][52][52];
int n,m;

ll get(int y1, int x1, int y2, int x2){
	return p[y2][x2]-p[y1-1][x2]-p[y2][x1-1]+p[y1-1][x1-1];
}

ll solve(int y1, int x1, int y2, int x2){
	if(dp[y1][x1][y2][x2]==-1){
		if(y1==y2 and x1==x2)
			dp[y1][x1][y2][x2]=0;
		else{
			ll res=1e18;

			for(int i=y1+1;i<=y2;++i){
				ll pay=solve(y1,x1,i-1,x2)+solve(i,x1,y2,x2);
				res=min(res,pay);
			}
			for(int i=x1+1;i<=x2;++i){
				ll pay=solve(y1,x1,y2,i-1)+solve(y1,i,y2,x2);
				res=min(res,pay);
			}
			dp[y1][x1][y2][x2]=res+get(y1,x1,y2,x2);
		}
	}
	return dp[y1][x1][y2][x2];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j){
			cin>>t[i][j];
			p[i][j]=t[i][j]+p[i-1][j]+p[i][j-1]-p[i-1][j-1];
		}
	memset(dp,-1,sizeof(dp));
	cout<<solve(1,1,n,m);
}

