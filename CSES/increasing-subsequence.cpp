#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int n, tab[200007];
vector<int> dp;
int main() {
    ios;
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
		
	for(int i = 0; i < n; ++i) {
		int pos = lower_bound(dp.begin(), dp.end(), tab[i]) - dp.begin();
		if(pos == dp.size())
			dp.push_back(tab[i]);
		else
			dp[pos] = tab[i];
	}
	cout << dp.size();
}
