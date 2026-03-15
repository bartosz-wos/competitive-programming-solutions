#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll exp(ll a, ll w){
	ll ret=1;
	a%=mod;
	while(w){
		if(w&1)ret=ret*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return ret;
}

vector<int>berlekamp(vector<int>a){
	int n=a.size();
	if(!n)return vector<int>();
	vector<int>C={1},B={1};
	int L=0;
	ll b=1;
	for(int i=0,m=1;i<n;++i){
		ll d=0;
		for(int j=0;j<=L;++j)
			if(j<C.size())
				d=(d+1ll*C[j]*a[i-j])%mod;
		if(!d)++m;
		else{	
			vector<int>T=C;
			ll c=d*exp(b,mod-2)%mod;
			while(C.size()<=B.size()+m)C.push_back(0);
			for(int j=0;j<B.size();++j){
				C[j+m]=(C[j+m]-1ll*c*B[j])%mod;
				if(C[j+m]<0)C[j+m]+=mod;
			}
			if((L<<1)<=i){
				L=i+1-L;
				B=T;
				b=d;
				m=1;
			}else ++m;
		}
	}
	C.resize(L+1);
	return C;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<int>a(n);
	for(int&i:a)cin>>i;
	auto b=berlekamp(a);
	if(b.empty()){
		cout<<0<<'\n';
		return 0;
	}
	b.erase(b.begin());
	cout<<b.size()<<'\n';
	for(const int&i:b)cout<<(mod-(!i?mod:i))<<' ';
	cout<<'\n';
}
