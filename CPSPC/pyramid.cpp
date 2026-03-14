#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int, int>
using namespace std;

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<ll> arr(N);
	for(int i=0;i<N;i++) {
		scanf("%lld", &arr[i]);
	}
	
	vector<pair<ll, int> > ck((1 << N) - 1);
	
	for(int i=1;i<(1 << N);i++) {
		ll as = 1ll;
		bool v = 0;
		for(int k=0;k<N;k++) {
			if(i&(1 << k)) {
				as = (as * arr[k]) / (__gcd(as, arr[k])); 
				v ^= 1;
			}
		}
		if(v) ck[i - 1] = {as, 1};
		else ck[i - 1] = {as, -1};
	}
	
	while(M--) {
		ll a;
		scanf("%lld", &a);
		ll lf = 1ll, rg = 1e18, ans;
		while(lf <= rg) {
			ll mid = (lf + rg) / 2ll;
			ll as = 0ll;
			for(auto p : ck) {
				as += mid / p.fi * p.se;
			}
			if(as >= a){
				ans = mid;
				rg = mid - 1ll;
			} else lf = mid + 1ll;
		}
		printf("%lld\n", ans);
	}
}
