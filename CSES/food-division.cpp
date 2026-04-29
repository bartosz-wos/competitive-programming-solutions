#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n;
int a[200001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	for(int i=1,b;i<=n;++i){
		cin>>b;
		a[i]+=a[i-1]-b;
	}
	sort(a+1,a+1+n);
	ll ans=0;
	for(int i=1;i<=n;++i)
		ans+=abs(a[i]-a[(n+1)>>1]);
	cout << ans;
}
