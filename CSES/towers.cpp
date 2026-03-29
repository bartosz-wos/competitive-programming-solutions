#include<iostream>
#include<set>
using namespace std;
 
int n, p;
multiset<int> S;
int main() {
	cin >> n;
	multiset<int>::const_iterator it;
 
	for(int i = 0; i < n; ++i) {
		cin >> p;
		it = S.upper_bound(p);
		if(it == S.end())
			S.insert(p);
		else {
			S.erase(it);
			S.insert(p);
		}
	}
	cout << S.size();
}
