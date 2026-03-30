#include<iostream>
#include<algorithm>
using namespace std;
 
int n, tab[200007];
long long sum;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> tab[i], sum += tab[i];
	sort(tab, tab + n);
 
	cout << max(2LL * tab[n - 1], sum);
}
