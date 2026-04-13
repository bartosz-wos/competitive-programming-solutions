#include<iostream>
#include<vector>
#include<set>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
vector<int> lps;
set<int> ans;
string a;
 
void computelps(const string& pat, const int& M) {
	lps.resize(M);
	int i = 1, len = 0;
	while (i < M) {
		if (pat[i] == pat[len]) {
			lps[i] = ++len;
			++i;
		}
		else {
			if (len != 0)
				len = lps[len - 1];
			else {
				lps[i] = 0;
				++i;
			}
		}
	}
}
 
int main() {
	ios;
	cin >> a;
	computelps(a, a.length());
 
	int i = a.length() - 1;
	while (i > 0) {
		if (lps[i])
			ans.insert(lps[i]);
		i = lps[i] - 1;
	}
	for (const int& i : ans)
		cout << i << ' ';
}
