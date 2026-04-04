#include<bits/stdc++.h>
using namespace std;
map<string, int> mp;
string mp2[100001];
int k = 0, n = 5;
 
void rec(string s) {
	if(s.length() == n - 1) {
		mp[s] = ++k;
		mp2[k] = s;
		return;
	}
	rec(s + '0');
	rec(s + '1');
}
vector<pair<int, char>> g[100001];
 
void solve() {
	cin >> n;
	if(n == 1) {
		cout << "01";
		return;
	}
	rec("");
	int t = 1 << (n - 1);
	for(int i = 1; i <= t; ++i) {
		string x = mp2[i].substr(1, n - 2);
		g[i].push_back({mp[x + "0"], '0'});
		g[i].push_back({mp[x + "1"], '1'});
	}
	string path;
	stack<pair<int, char>> S;
	S.push({1, '#'});
	while(!S.empty()) {
		auto [i, c] = S.top();
		if(g[i].empty()) {
			if(c != '#')
				path += c;
			S.pop();
		}
		else {
			auto [j, c2] = g[i].back();
			g[i].pop_back();
			S.push({j, c2});
		}
	}
	path += mp2[1];
	cout << path << '\n';
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
