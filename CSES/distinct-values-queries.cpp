#include<bits/stdc++.h>
using namespace std;
 
int tab[200001];
int T[200001];
int ans[200001];
int n, q;
vector< array<int, 2> > qr[200001];
map<int, int> mp;
 
int query(int x) {
	int ans = 0;
	while(x)
		ans += T[x], x -= x & -x;
	return ans;
}
 
void upd(int x, int val) {
	while(x <= n)
		T[x] += val, x += x & -x;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
 
	for(int i = 0; i < q; ++i) {
		int a, b;
		cin >> a >> b;
		qr[a].push_back({b, i});
	}
	for(int i = n; i; --i) {
		int p = tab[i - 1];
		if(mp.count(p))
			upd(mp[p], -1);
		mp[p] = i;
		upd(i, 1);
		for(const auto& k : qr[i])
			ans[k[1]] = query(k[0]);
	}
	for(int i = 0; i < q; ++i)
		cout << ans[i] << ' ';
 
}

