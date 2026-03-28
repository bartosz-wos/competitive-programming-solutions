#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
using pi = pair<int, int>;
 
int n;
vector<pi> tab;
int main() {
	cin >> n;
	tab.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> tab[i].first >> tab[i].second;
 
	sort(tab.begin(), tab.end(), [](const pi& a, const pi& b){return a.second < b.second;});
 
	int end = tab[0].second, ans = 1;
	for(int i = 1; i < n; ++i) {
		if(tab[i].first >= end) {
			end = tab[i].second;
			++ans;
		}
	}
	cout << ans;
}
