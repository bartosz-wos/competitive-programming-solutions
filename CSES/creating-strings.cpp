#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
 
set <string> S;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string a;
	cin >> a;
	sort( a.begin(), a.end() );
 
	do {
		S.insert(a);
	} while (next_permutation(a.begin(), a.end()));
 
	cout << S.size() << '\n';
 
	for (const string& i : S)
		cout << i << '\n';

