#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using matrix=vector<vector<ll>>;

constexpr int mod=998244353;

int n;
ll k;

matrix mul(const matrix&a, const matrix&b){
	matrix c(n,vector<ll>(n));
	for(int i=0;i<n;++i)
		for(int k=0;k<n;++k){
			if(!a[i][k])continue;
			for(int j=0;j<n;++j){
				c[i][j]+=a[i][k]*b[k][j]%mod;
				if(c[i][j]>=mod)c[i][j]-=mod;
			}
		}
	return c;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	matrix a(n,vector<ll>(n)),ret(n,vector<ll>(n));
	for(int i=0;i<n;++i)ret[i][i]=1;
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			cin>>a[i][j];
	while(k){
		if(k&1)ret=mul(ret,a);
		a=mul(a,a);
		k>>=1;
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j)
			cout<<ret[i][j]<<' ';
		cout<<'\n';
	}
}
