#include <bits/stdc++.h>
using namespace std;
 
#define ff first
#define ss second
#define all(a) a.begin(), a.end()
int n, k;
vector<pair<int, int> > ans;
int cur;
vector<int> a;
void f(int x){
	if(x < 0) return;
	if(cur >= n or a[cur] >= x){
		
		if(cur < n && a[cur] == x){
			ans.push_back({x, 0});
			cur++;
		}else{
			ans.push_back({x, 1});
		}
	}else{
		f(x-1);
		f(x-1);
	}
}
vector<int> add;
void split(int x){
	if(k == 0 or x == 0){
		add.push_back(x);
	}else{
		k--;
		split(x-1);
		split(x-1);
	}
} 
 
 
main(){
	cin >> n >> k;
	a.resize(n);
	for(int i = 0;i < n; i++){
		cin >> a[i];
	}

	f(30);
	if(ans.size() == n + k){
		for(auto [x, y] : ans) cout << x << ' ';
		return 0;
	}
	k = k - (int)ans.size() + n;
	vector<int> all;
	for(auto [x, y] : ans){
		if(!y){
			all.push_back(x);
			continue;
		}
		add.clear();
		split(x);
		for(int ax : add) all.push_back(ax);
	}
	for(int x : all) cout << x << ' ';
	return 0;
}
