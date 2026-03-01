#include<bits/stdc++.h>
using namespace std;
using ll=long long;

uint16_t dp[1005][1005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int q;
	cin>>q;
	string s,t;
	cin>>s>>t;
	int n=s.size();
	int m=t.size();
	for(int i=0;i<=m;++i)
		dp[0][i]=i;
	for(int i=1;i<=n;++i){
		int lst=0;
		dp[i][0]=0;
		for(int j=1;j<=m;++j){
			int c=dp[i-1][j];
			if(s[i-1]==t[j-1]){
				dp[i][j]=lst;
				lst=c;
			}else {
				dp[i][j]=max(c,lst);
				lst=min(c,lst);
			}
		}
	}
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		int ret=0;
		const uint16_t*r=dp[a];
		for(int i=b+1;i<=c;++i)
			ret+=r[i]<=b;
		cout<<ret<<'\n';
	}
}
