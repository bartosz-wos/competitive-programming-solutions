#include<iostream>
#include<set>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int n, m, p, customer;
multiset<int> tickets;
int main() {
	ios;
	cin >> n >> m;
 
	for(int i = 0; i < n; ++i) {
		cin >> p;
		tickets.insert(p);
	}
 
	multiset<int>::const_iterator it;
	while(m--) {
		cin >> p;
		it = tickets.upper_bound(p);
		if( it != tickets.begin() && tickets.size() >= 1) {
			--it;
			cout << *it << '\n';
			tickets.erase(it);
		}
		else {
			cout << -1 << '\n';
		}
	}
 
}
