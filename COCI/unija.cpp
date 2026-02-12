#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define ar array
#define int long long
 
const int N = 5e5 + 20;
const int INF = 1e17;
const int MOD = 8;
const int X = 4000;
const int LOG = 21;
 
#pragma GCC optimize("O3,Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
 
bitset<N> del;
 
bool cmp(ar<int, 2> a, ar<int, 2> b){
	if(a[0] == b[0])return a[1] > b[1];
	return a[0] < b[0];
}
 
signed main(){ios_base::sync_with_stdio(false);cin.tie(0);
	int n;
	cin>>n;
	ar<int, 2> A[n];
	for(int i = 0;i  < n;i++){
		cin>>A[i][0]>>A[i][1];
	}
	sort(A, A + n, cmp);
	
	vector<ar<int, 2> > v;
	v.push_back(A[0]);
	for(int i = 1;i < n;i++){
		while(v.back()[1] < A[i][1])v.pop_back();
		v.push_back(A[i]);
	}
	
	int ans = v[0][0] * v[0][1];
	for(int i = 1;i < v.size();i++)ans += v[i][0] * v[i][1] - v[i-1][0] * v[i][1];
	cout<<ans;
}
