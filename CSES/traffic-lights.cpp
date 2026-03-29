#include<iostream>
#include<set>
#include<queue>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int n, q, p, ans;
set<int> S;
multiset<int> Q;
int main() {
	ios;
	cin >> n >> q;
	ans = n + 1;
	S.insert(0);
	S.insert(n);
	Q.insert(n);
	set<int>::const_iterator it1, it2;
	while (q--) {
		cin >> p;
		it2 = S.upper_bound(p);
		it1 = next(it2, -1);
		Q.erase(Q.find(*it2 - *it1));
		Q.insert(p - *it1);
		Q.insert(*it2 - p);
		S.insert(p);
		cout << *next(Q.end(), -1) << ' ';
	}
}
