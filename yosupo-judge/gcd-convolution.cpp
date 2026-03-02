#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

int a[1000005];
int b[1000005];
ll a2[1000005];
ll b2[1000005];
ll c[1000005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=1;i<=n;++i)cin>>b[i];
	for(int i=1;i<=n;++i)
		for(int j=i;j<=n;j+=i){
			a2[i]+=a[j];
			if(a2[i]>=mod)a2[i]-=mod;
			b2[i]+=b[j];
			if(b2[i]>=mod)b2[i]-=mod;
		}
	for(int i=1;i<=n;++i)
		c[i]=a2[i]*b2[i]%mod;
	for(int i=n;i>=1;--i)
		for(int j=i<<1;j<=n;j+=i){
			c[i]-=c[j];
			if(c[i]<0)c[i]+=mod;
		}
	for(int i=1;i<=n;++i)
		cout<<c[i]<<' ';
	cout<<'\n';
}
