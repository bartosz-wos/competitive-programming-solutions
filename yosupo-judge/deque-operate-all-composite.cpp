#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;

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

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int q;
	cin>>q;
	deque<pi>dq;
	ll c=1,d=0;
	while(q--){
		int t;
		cin>>t;
		if(t<=1){
			ll a,b;
			cin>>a>>b;
			if(!t)dq.push_front({a,b});
			else dq.push_back({a,b});
			ll nc,nd;
			if(!t)nc=c*a%mod,nd=(c*b+d)%mod;
			else nc=c*a%mod,nd=(a*d+b)%mod;
			c=nc;
			d=nd;
		}else if(t<=3){
			ll a,b;
			if(t==2)a=dq.front()[0],b=dq.front()[1],dq.pop_front();
			else a=dq.back()[0],b=dq.back()[1],dq.pop_back();
			ll inv=exp(a,mod-2);

			ll nc,nd;
			if(t==2){
				nc=c*inv%mod;
				nd=(d-nc*b%mod)%mod;
				if(nd<0)nd+=mod;
			}else{
				nc=c*inv%mod;
				nd=(d-b)%mod;
				if(nd<0)nd+=mod;
				nd=nd*inv%mod;
			}
			c=nc;
			d=nd;
		}else{
			ll x;
			cin>>x;
			cout<<(c*x+d)%mod<<'\n';
		}
	}
}
