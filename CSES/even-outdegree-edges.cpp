#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<array>
#include<climits>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<chrono>
#include<functional>
#include<numeric>
using namespace std;
using ll = long long;
using ar2 = array<ll, 2>;
using ar3 = array<ll, 3>;
using ar4 = array<ll, 4>;
#define rep(i, s, e) for(int i = s; i <= e; ++i)
constexpr ll inf = 1LL << 60;
constexpr int mod = 1e9 + 7;
constexpr int poz = 20;
constexpr int u = 1 << (poz - 1);
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
int n, m;
int vis[100001], odd[100001], timer = 1;
vector<int> g[100001];
vector<ar2> ans;
 
void dfs(int v, int e) {
	vis[v] = timer++;
	for (const int& i : g[v]) {
		if (i == e) continue;
		if (!vis[i]) {
			dfs(i, v);
			if (odd[i]) {
				ans.push_back({ i, v });
				odd[i] = 0;
			}
			else {
				ans.push_back({v, i});
				odd[v] ^= 1;
			}	
		}
		else if(vis[v] > vis[i]) {
			ans.push_back({ v, i });
			odd[v] ^= 1;
		}
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs(i, -1);
 
	if (accumulate(odd + 1, odd + n + 1, 0)) cout << "IMPOSSIBLE";
	else
		for (const ar2& i : ans)
			cout << i[0] << ' ' << i[1] << '\n';
}
