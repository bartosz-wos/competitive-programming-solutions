#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll exp(ll a, ll w, ll m){
	ll res=1%m;
	a%=m;
	while(w){
		if(w&1)res=res*a%m;
		a=a*a%m;
		w>>=1;
	}
	return res;
}

ll gcd(ll a, ll b){
	if(!b)return a;
	return gcd(b,a%b);
}

ll d_log(ll a, ll b, ll m){
	a%=m;
	b%=m;
	if(m==1 or b==1)return 0;
	if(!a)return !b?1:-1;
	int k=1,ad=0,g;
	while((g=gcd(a,m))>1){
		if(b==k)return ad;
		if(b%g)return -1;
		b/=g;
		m/=g;
		++ad;
		k=(1ll*k*a/g)%m;
	}
	int n=sqrt(m)+1;
	int an=1;
	for(int i=0;i<n;++i)
		an=(1ll*a*an)%m;
	unordered_map<int,int>mp;
	for(int q=0,c=b;q<=n;++q){
		mp[c]=q;
		c=(1ll*a*c)%m;
	}
	for(int p=1,c=k;p<=n;++p){
		c=(1ll*an*c)%m;
		if(mp.count(c))return n*p-mp[c]+ad;
	}
	return -1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		ll a,b,m;
		cin>>a>>b>>m;
		cout<<d_log(a,b,m)<<'\n';
	}
}
