#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXN=1005;
constexpr int MAXM=105;
constexpr int MAXK=26;
constexpr int mod=1e9+7;
 
int n;
string s;
 
int kmp[MAXM];
 
void calc(){
	kmp[0]=0;
	for(int i=1,j;i<s.size();++i){
		j=kmp[i-1];
		while(j>0 and s[i]!=s[j])
			j=kmp[j-1];
		if(s[i]==s[j])++j;
		kmp[i]=j;
	}
}
 
ll dp[MAXN][MAXM];
 
ll solve(int i, int j){
	if(dp[i][j]!=-1)return dp[i][j];
	if(i==n) return dp[i][j]=(j==s.size());
	if(j==s.size()) return dp[i][j]=MAXK*solve(i+1,j)%mod;
	ll res=0;
	for(int k=0,t;k<MAXK;++k){
		t=j;
 
		while(t>0 and s[t]-65!=k)
			t=kmp[t-1];
		if(s[t]-65==k)++t;
 
		res+=solve(i+1,t);
		res%=mod;
	}
	return dp[i][j]=res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	memset(dp,-1,sizeof dp);
	cin>>n>>s;
	calc();
	cout<<solve(0,0);
}
