#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll res=0;
 
int n;
ll dp[1000001];
int s[1000001];
 
void sieve(){
	for(int i=2;i*i<=1e6;++i)
		if(!s[i])
			for(int j=i*i;j<=1e6;j+=i)
				if(!s[j])
					s[j]=i;
}
 
vector<int> factor(int x){
	set<int>S;
	while(s[x]){
		S.insert(s[x]);
		x/=s[x];
	}
	if(x!=1) S.insert(x);
	vector<int>ans;
	for(const int&i:S)
		ans.push_back(i);
	return ans;
}
 
void solve(int k){
	vector<int>f=factor(k);
	int SZ=f.size();
	for(int mask=0;mask<(1<<SZ);++mask){
		int mul=1;
		for(int i=0;i<f.size();++i)
			if(mask&(1<<i))
				mul*=f[i];
		res+=(__builtin_popcount(mask)&1?-dp[mul]:dp[mul]);
		++dp[mul];
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	sieve();
	cin>>n;
	while(n--){
		int k;
		cin>>k;
		solve(k);
	}
	cout<<res;
}
