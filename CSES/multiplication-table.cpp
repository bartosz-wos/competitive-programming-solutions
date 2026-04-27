#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
ll n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	ll l=1,r=n*n,mid=0,leq=0;
	while(l<r){
		mid=(l+r)>>1;
		leq=0;
		for(int i=1;i<=n;++i)
			leq+=min(n,mid/i);
		if(leq>=(n*n+1)>>1)
			r=mid;
		else
			l=mid+1;
	}
	cout<<r;
}
