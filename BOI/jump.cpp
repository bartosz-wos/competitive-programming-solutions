#include <iostream>
#include <algorithm>
using namespace std;

int n, a[110][110];
string ans[150][150];

string add(string s, string t) {
	int tmp;
	string answer = "";
	if (s.length() > t.length()) {
		reverse(t.begin(),t.end());
		tmp = t.length();
		for (int i = tmp; i < s.length(); i++) t += '0';
		reverse(t.begin(),t.end());
	} else if (s.length() < t.length()) {
		reverse(s.begin(),s.end());
		tmp = s.length();
		for (int i = tmp; i < t.length(); i++) s += '0';
		reverse(s.begin(),s.end());
	}
	tmp = 0;
	for (int i = s.length()-1; i >= 0; i--) {
		answer += ((s[i]-48)+(t[i]-48)+tmp)%10+48;
		tmp = ((s[i]-48)+(t[i]-48)+tmp)/10;
	}
	if (tmp) answer += tmp+48;
	reverse(answer.begin(),answer.end());
	return answer;
}

int main() {
	cin >> n;
	for (int i = 1; i <= 140; i++) for (int j = 1; j <= 140; j++) ans[i][j] = "0";
	for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> a[i][j];
	ans[1][1] = "1";
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i][j] != 0) {
			    ans[i+a[i][j]][j] = add(ans[i+a[i][j]][j],ans[i][j]);
				ans[i][j+a[i][j]] = add(ans[i][j+a[i][j]],ans[i][j]);
			}
		}
	}
	cout << ans[n][n] << endl;
}
