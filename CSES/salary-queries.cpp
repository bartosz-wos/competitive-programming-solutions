#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using ar = array<int, 2>;
using Tree = tree<ar, null_type, less<ar>, rb_tree_tag,tree_order_statistics_node_update>;
int n, q;
static int tab[200001];
Tree T;
 
int main() {
	ios_base::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i) {
		cin >> tab[i];
		T.insert({tab[i], i});
	}
 
	while(q--) {
		char p;
		cin >> p;
		if(p == '!') {
			int index, val;
			cin >> index >> val;
			T.erase({tab[index], index});
			tab[index] = val;
			T.insert({tab[index], index});
		}
		else {
			int a, b;
			cin >> a >> b;
			cout << T.order_of_key({b, (int)1e9+1}) - T.order_of_key({a - 1, (int)1e9+1}) << '\n';
		}
	}
}
