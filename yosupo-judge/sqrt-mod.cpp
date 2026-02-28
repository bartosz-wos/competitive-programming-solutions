#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using lll=__int128;

ll exp(ll a, ll w, ll m){
        a%=m;
        ll res=1;
        while(w){
                if(w&1)res=res*a%m;
                a=a*a%m;
                w>>=1;
        }
        return res;
}

ll mod_sqrt(ll a, ll m){
	if(!a)return 0;
	if(m==2)return a%m;
	if(exp(a,(m-1)/2,m)!=1)return -1;
	if(m%4==3)return exp(a,(m+1)/4,m);
	ll s=0,d=m-1;
	while(~d&1)d>>=1,++s;
	ll n=2;
	while(exp(n,(m-1)/2,m)!=m-1)++n;
	ll res=exp(a,(d+1)/2,m);
	ll c=exp(n,d,m);
	ll t=exp(a,d,m);
	ll val=s;
	while(t!=1){
		ll i=0,temp=t;
		while(temp!=1 and i<val)temp=temp*temp%m,++i;
		if(i==val)return -1;
		ll b=c;
		for(int j=0;j<val-i-1;++j)
			b=b*b%m;
		val=i;
		c=b*b%m;
		t=t*c%m;
		res=res*b%m;
	}
	return min(res,m-res);
}

int main(){
	ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--){
		ll a,p;
		cin>>a>>p;
		cout<<mod_sqrt(a,p)<<'\n';
	}
}
