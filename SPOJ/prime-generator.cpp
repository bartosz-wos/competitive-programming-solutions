#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
void solve(){
	ll l,r;
	cin>>l>>r;
	ll lim=sqrt(r);
	vector<char>mark(lim+1,1);
	vector<ll>primes;
	for(ll i=2;i<=lim;++i)
		if(mark[i]){
			primes.push_back(i);
			for(ll j=i*i;j<=lim;j+=i)
				mark[j]=0;
		}
	vector<char>P(r-l+1,1);
	for(const ll&p:primes)
		for(ll j=max(p*p,(l+p-1)/p*p);j<=r;j+=p)
			P[j-l]=0;
	if(l==1)P[0]=0;
	for(ll i=l;i<=r;++i)
		if(P[i-l])cout<<i<<'\n';
	cout<<'\n';
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;cin>>t;
	while(t--)solve();
}

