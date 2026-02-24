#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll a[1050][1050];
ll b[1050][1050];
ll c[1050][1050];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=0;i<n;++i)
		for(int j=0;j<m;++j)
			cin>>a[i][j];
	for(int i=0;i<m;++i)
		for(int j=0;j<k;++j)
			cin>>b[i][j];
	for(int i=0;i<n;++i)
		for(int q=0;q<m;++q){
			if(!a[i][q])continue;
			for(int j=0;j<k;++j){
				c[i][j]+=a[i][q]*b[q][j]%mod;
				if(c[i][j]>=mod)c[i][j]-=mod;
			}
		}
	for(int i=0;i<n;++i){
		for(int j=0;j<k;++j)
			cout<<c[i][j]<<' ';
		cout<<'\n';
	}
}
