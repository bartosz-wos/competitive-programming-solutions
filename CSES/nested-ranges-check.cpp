#include<iostream>
#include<algorithm>
#include<bitset>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
using pi = pair<int, int>;
bitset<200007> contains, contained;
#define l first.first
#define r first.second
auto comp = [](const pair<pi, int>& a, const pair<pi, int>& b) { if (a.l == b.l) return a.r > b.r; return a.l < b.l; };
 
int n;
pair<pi, int> tab[200007];
int main() {
	ios;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> tab[i].l >> tab[i].r, tab[i].second = i;
 
	sort(tab, tab + n, comp);
	int en = 1e9 + 7;
	for (int i = n - 1; i >= 0; --i) {
		if (tab[i].r >= en)
			contains[tab[i].second] = 1;
		en = min(en, tab[i].r);
	}
	en = 0;
	for (int i = 0; i < n; ++i) {
		if (tab[i].r <= en)
			contained[tab[i].second] = 1;
		en = max(en, tab[i].r);
	}
	for (int i = 0; i < n; ++i)
		cout << contains[i] << ' ';
	cout << '\n';
	for (int i = 0; i < n; ++i)
		cout << contained[i] << ' ';
}
