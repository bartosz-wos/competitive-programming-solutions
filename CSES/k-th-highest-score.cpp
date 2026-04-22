#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,k;
	cin>>n>>k;
	const ll POSINF=2000000005LL;
	const ll NEGINF=-2000000005LL;
	vector<ll> cacheF(n+2,LLONG_MIN),cacheS(n+2,LLONG_MIN);
	auto askF=[&](int i)->ll{
		if(i<=0) return POSINF;
		if(i>n) return NEGINF;
		if(cacheF[i]!=LLONG_MIN) return cacheF[i];
		cout<<'F'<<' '<<i<<endl;
		cout.flush();
		ll x;cin>>x;
		cacheF[i]=x;
		return x;
	};
	auto askS=[&](int i)->ll{
		if(i<=0) return POSINF;
		if(i>n) return NEGINF;
		if(cacheS[i]!=LLONG_MIN) return cacheS[i];
		cout<<'S'<<' '<<i<<endl;
		cout.flush();
		ll x;cin>>x;
		cacheS[i]=x;
		return x;
	};
	int lo=max(0,k-n),hi=min(k,n);
	int best=lo-1;
	while(lo<=hi){
		int mid=(lo+hi)/2;
		ll a=askF(mid);
		ll b=askS(k-mid);
		if(a>b){
			best=mid;
			lo=mid+1;
		}else{
			hi=mid-1;
		}
	}
	int idx1=best+1;
	int idx2=k-best;
	ll cand1=(1<=idx1 && idx1<=n)?askF(idx1):NEGINF;
	ll cand2=(1<=idx2 && idx2<=n)?askS(idx2):NEGINF;
	ll ans=max(cand1,cand2);
	cout<<'!'<<' '<<ans<<endl;
	cout.flush();
	return 0;
}

