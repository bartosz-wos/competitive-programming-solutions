#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
 
template<typename T>
using order_set =  tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define ar array
#define ld long double
#define all(v) v.begin(), v.end()
#define int long long

#pragma GCC optimize("unroll-loops,O3,Ofast")

const int inf = 1e15 + 20;
const int maxN = 4e5 + 20;


signed main(){ios_base::sync_with_stdio(false);cin.tie(0);
	int n, q, s, t;
	cin>>n>>q>>s>>t;
	int A[n];
	int prv;
	cin>>prv;
	for(int i = 0;i < n;i++){
		int x;
		cin>>x;
		A[i] = prv - x;
		prv = x;
	}
	int ans = 0;
	for(int i = 0;i < n;i++){
		if(A[i] > 0)ans += t * A[i];
		else ans += s * A[i];
	}
	
	while(q--){
		int l, r, v;
		cin>>l>>r>>v;
		--l;
		if(A[l] >= 0)ans -= t * A[l];
		else ans -= s * A[l];
		A[l] -= v;
		if(A[l] >= 0)ans += t * A[l];
		else ans += s * A[l];
		if(r < n){
			if(A[r] >= 0)ans -= t * A[r];
			else ans -= s * A[r];
			A[r] += v;
			if(A[r] >= 0)ans += t * A[r];
			else ans += s * A[r];
		}
		cout<<ans<<'\n';
	}
	
}
