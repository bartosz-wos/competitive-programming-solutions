#include "libmean.h"
#include <bits/stdc++.h>
using namespace std;

int ans[100];

int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	memset(ans,-1,sizeof(ans));
	int n = Init();
	queue<int> q;
	for (int i=1; i<=n; ++i) q.push(i);
	while (q.size() > 4){
		vector<int> idx;
		for (int i=0; i<5; ++i){
			idx.emplace_back(q.front());
			q.pop();
		}
		vector<pair<int,int>> queries = {
			{Meandian(idx[0],idx[1],idx[2],idx[3]),idx[4]},
			{Meandian(idx[0],idx[1],idx[2],idx[4]),idx[3]},
			{Meandian(idx[0],idx[1],idx[3],idx[4]),idx[2]},
			{Meandian(idx[0],idx[2],idx[3],idx[4]),idx[1]},
			{Meandian(idx[1],idx[2],idx[3],idx[4]),idx[0]}
		};
		sort(queries.begin(),queries.end());
		ans[queries[2].second-1] = queries[0].first+queries[4].first-queries[2].first;
		for (int i=0; i<5; ++i){
			if (i != 2) q.emplace(queries[i].second);
		}
	}
	Solution(ans);
	return 0;
}
