#include "molecules.h"
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;
#define ll long long
typedef pair<ll,int> pii;
 
ll le = 0, ri = -1, sum = 0;
 
vector<int> find_subset(int l, int r, vector<int> w) {
	vector <pii> ma; int n = (int)w.size();
	for(int i=0; i<n; i++) ma.pb({w[i], i});
	sort(ma.begin(), ma.end()); 
	for(int i=0; i<n; i++){
		while(ri+1 < n && sum < l){
			ri++; sum += ma[ri].fi;
		}
		if(l<=sum && sum<=r){
			le = i; break;
		}
		sum -= ma[i].fi;
	}
	vector <int> ans;
	if(l<=sum && sum<=r)
		for(int i=le; i<=ri; i++) ans.pb(ma[i].se);
	sort(ans.begin(), ans.end());
    	return ans;
}
