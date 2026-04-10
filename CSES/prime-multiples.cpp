#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll n,k;
ll a[20];
ll res;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	for(int i=0;i<k;++i)
		cin>>a[i];
	ll res=0;
	for(int mask=0;mask<(1<<k);++mask){
		ll temp=n;
		for(int i=0;i<k;++i)
			if(mask&(1<<i))
				temp/=a[i];
		res+=(__builtin_popcount(mask)&1?temp:-temp);
	}
	res+=n;
	cout<<res;
}
