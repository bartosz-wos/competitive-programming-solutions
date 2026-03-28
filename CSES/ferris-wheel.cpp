#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 7;
 
int n, x, tab[MAXN], ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	cin >> n >> x;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
	sort(tab, tab + n);
 
	int i = 0, j = n - 1;
 
	while(i <= j) {
		if(tab[i] + tab[j] <= x) {
			++ans;
			++i;
			--j;
		}
		else {
			++ans;
			--j;
		}
	}
	cout << ans;
}
