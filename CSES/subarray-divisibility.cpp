#include <iostream>
using namespace std;
 
int n, p,l;
long long mod[200007];
long long sum, ans;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
 
	for(int i = 0; i < n; ++i) {
		cin >> p;
		sum += p;
		++mod[((sum % n )+ n) % n];
	}
 
	for(int i = 0; i < n; ++i)
		ans += (mod[i] * (mod[i] - 1)) >> 1;
 
	cout << ans + mod[0];
}
