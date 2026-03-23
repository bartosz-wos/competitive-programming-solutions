#include<iostream>
#include<set>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define pb(i) insert(i)
 
auto comp = [](const int& a, const int& b) {return a > b; };
 
int n;
long long sum;
set<int, decltype(comp)> tab1(comp), tab2(comp);
int main() {
	ios;
	cin >> n;
	sum = (n * (n + 1)) >> 1;
 
	if (sum & 1) {
		cout << "NO";
		return 0;
	}
	int i = 1, j = n;
	if (!(n & 1)) {
		while (j - i > 1) {
			if (i & 1) {
				tab1.pb(i);
				tab1.pb(j);
			}
			else {
				tab2.pb(i);
				tab2.pb(j);
			}
			++i;
			--j;
		}
		tab2.pb(i);
		tab2.pb(j);
	}
	else {
		j = n - 1;
		while (j - i > 1) {
			if (i & 1) {
				tab1.pb(i);
				tab1.pb(j);
			}
			else {
				tab2.pb(i);
				tab2.pb(j);
			}
			++i;
			--j;
		}
		tab2.pb(i);
		tab2.pb(j);
		tab1.pb(n);
	}
	cout << "YES\n";
	cout << tab1.size() << '\n';
	for (const int& i : tab1)
		cout << i << ' ';
	cout << '\n' << tab2.size() << '\n';
	for (const int& i : tab2)
		cout << i << ' ';

