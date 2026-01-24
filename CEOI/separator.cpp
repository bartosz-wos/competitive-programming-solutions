#include<bits/stdc++.h>
#define ll long long
#define mod 1000000000
using namespace std;
ll s,cnt,mx,b,a,i,n;
multiset<ll> t;
multiset<ll> ::iterator it;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	mx=-1;
	cin >> n;
	for(i=1;i<=n;i++){
		cin >> b;
		a=(b+s)%mod;
		while(true){
			it=t.lower_bound(a);
			if(it==t.end()) break;
			cnt--;
			t.erase(it);
		}
		if(a>mx){
			cnt++;
			mx=a;
			t.insert(a);
		}
		s=cnt;
		cout << cnt << "\n";
	}
}
