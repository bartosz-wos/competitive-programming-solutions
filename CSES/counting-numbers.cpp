#include<bits/stdc++.h>
using namespace std;
using ll=long long;
ll dp[19];
 
ll solve(ll n){
	if(n==-1)
		return 0;
	if(n==0)
		return 1;
	string s=to_string(n);
	ll res=0;
	for(int i=0;i<s.length();++i)
		res+=dp[i];
	int prev=0;
	for(int i=0;i<s.length();++i){
		int digit=s[i]-48;
		int diff=s.length()-i-1;
		int below=prev<digit?digit-1:digit;
		res+=digit==0?0:below*dp[diff];
		if(digit==prev)
			return res;
		prev=digit;
	}
	return res+1;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll a,b;
	cin>>a>>b;
	dp[0]=1;
	for(int i=1;i<19;++i)
		dp[i]=dp[i-1]*9;
	cout<<solve(b)-solve(a-1);
}
