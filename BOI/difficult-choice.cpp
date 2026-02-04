#include <bits/stdc++.h>
#include "books.h"
using namespace std;
#define all(a) begin(a),end(a)
using vi = vector<int>;
long long sum, a[100010];

void solve(int n, int K, long long A, int S) {
	vi ans(K,0); iota(all(ans),1);
	for(int i = 1; i <= K; i++) 
		a[i]=skim(i), sum+=a[i];
	if(sum>2*A) impossible();
	int l = K, r = n;
	while(l<r){
		int mid = (l+r+1)/2;
		if(sum-a[K]+skim(mid)<=2*A) l=mid;
		else r=mid-1;
	}
	deque<int> dq(K,0); iota(all(dq),1);
	for(int i = 0; i<=K; i++){
		sum-=a[K-i]; sum+=skim(l-i);
		dq.pop_back(); dq.push_front(l-i);
		if(sum>=A) answer(vi(all(dq)));
	}
	impossible();
}
