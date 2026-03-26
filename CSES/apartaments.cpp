#include <iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 7;
 
int n, m, k, a[MAXN], b[MAXN], ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m >> k;
	for(int i = 0; i < n; ++i)
		cin >> a[i];
	for(int i = 0; i < m; ++i)
		cin >> b[i];
	sort(a, a + n);
	sort(b, b + m);
 
	for(int i = 0, j = 0; i < n; ++i) {
		while(j < m && b[j] < a[i] - k)
			++j;
		if(j < m && b[j] <= a[i] + k) {
			++ans;
			++j;
		}
	}
	cout << ans;
}
