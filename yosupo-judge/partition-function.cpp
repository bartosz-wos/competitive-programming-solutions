#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;

	vector<ll>p(n+1,0);
	for(int i=0;i<=n;++i){
		ll sum=i==0;
		for(int k=1;;++k){
			int p1=k*(3*k-1)>>1;
			int p2=k*(3*k+1)>>1;
			if(p1>i)break;
			if(k&1){
				sum+=p[i-p1];
				if(sum>=mod)sum-=mod;
				if(p2<=i){
					sum+=p[i-p2];
					if(sum>=mod)sum-=mod;
				}
			}else{
				sum-=p[i-p1];
				if(sum<0)sum+=mod;
				if(p2<=i){
					sum-=p[i-p2];
					if(sum<0)sum+=mod;
				}
			}
		}
		cout<<(p[i]=sum)<<' ';
	}
	cout<<'\n';
}
