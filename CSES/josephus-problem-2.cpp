#include<iostream>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
indexed_set S;
int n, k, p;
int main() {
	ios;
	cin >> n >> k;
	for(int i = 1; i <= n; ++i)
		S.insert(i);
 
	p = 0;
	auto it = S.begin();
	while(!S.empty()) {
		p = (p + k) % S.size();
		it = S.find_by_order(p);
		cout << *it << ' ';
		S.erase(it);
	}
}
