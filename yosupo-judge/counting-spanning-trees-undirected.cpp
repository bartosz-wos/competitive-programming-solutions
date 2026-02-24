#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll exp(ll a, ll w){
	a%=mod;
	ll ret=1;
	while(w){
		if(w&1)ret=ret*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return ret;
}

int deg[505];
vector<vector<ll>>M;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	if(n==1){
		cout<<1<<'\n';
		return 0;
	}
	M.resize(n,vector<ll>(n,0));
	while(m--){
		int a,b;
		cin>>a>>b;
		if(a==b)continue;
		++deg[a];
		++deg[b];
		--M[a][b];
		--M[b][a];
		if(M[a][b]<0)M[a][b]+=mod;
		if(M[b][a]<0)M[b][a]+=mod;
	}
	for(int i=0;i<n;++i)
		M[i][i]=deg[i];
	for(int i=0;i<n;++i)
		M[i].pop_back();
	M.pop_back();
	--n;

	ll det=1;
	for(int i=0;i<n;++i){
		int p=-1;
		for(int j=i;j<n;++j)
			if(M[j][i]){
				p=j;
				break;
			}
		if(p==-1){
			det=0;
			break;
		}
		if(p!=i){
			swap(M[i],M[p]);
			det=mod-det;
		}
		det=det*M[i][i]%mod;
		ll inv=exp(M[i][i],mod-2);
		for(int j=i+1;j<n;++j){
			if(!M[j][i])continue;
			ll f=M[j][i]*inv%mod;
			for(int k=i;k<n;++k)
				M[j][k]=(M[j][k]-f*M[i][k]%mod+mod)%mod;
		}
	}
	cout<<det<<'\n';
}
