#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

constexpr int mod=998244353;

pi a[100005];
int ans[100005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	for(int i=0;i<t;++i){
		cin>>a[i][0];
		a[i][1]=i;
	}	
	sort(a,a+t);
	ll ret=1;
	int cur=0;

	for(int i=0;i<t;++i){
		while(cur+8<=a[i][0]){
			ll p1=1LL*(cur+1LL)*(cur+2LL)%mod;
			ll p2=1LL*(cur+3LL)*(cur+4LL)%mod;
			ll p3=1LL*(cur+5LL)*(cur+6LL)%mod;
			ll p4=1ll*(cur+7LL)*(cur+8LL)%mod;;
			ret=ret*p1%mod*p2%mod*p3%mod*p4%mod;
			cur+=8;
		}
		while(cur<a[i][0]){
			++cur;
			ret=ret*(ll)cur%mod;
		}
		ans[a[i][1]]=ret;
	}
	for(int i=0;i<t;++i)
		cout<<ans[i]<<'\n';
}
