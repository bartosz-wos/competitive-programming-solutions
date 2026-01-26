#include <bits/stdc++.h>
#define long long long

using namespace std;

const int N = 25000 * 20;
const int S = 26;

struct Trie {
	int c[N + 1][S], n;
	bool e[N + 1];
	int d[N + 1];
	string t;
	Trie() : n(0) {
		clean(n);
		t = "";
	}
	void clean(int u) {
		fill(c[u], c[u] + S, 0);
		e[u] = false;
	}
	void insert(string &s) {
		int u = 0;
		for (int i = 0; i < (int) s.size(); i++) {
			int &v = c[u][s[i] - 'a'];
			if (v == 0) {
				n = n + 1;
				clean(n);
				v = n;
			}
			u = v;
		}
		e[u] = true;
	}
	void DFS1(int u) {
		d[u] = 1;
		for (int i = 0; i < S; i++) {
			int v = c[u][i];
			if (v > 0) {
				DFS1(v);
				d[u] = max(d[u], d[v] + 1);
			}
		}
	}
	void DFS2(int u) {
		if (e[u] == true) {
			t += 'P';
		}
		for (int i = 0; i < S; i++) {
			int v = c[u][i];
			if (v > 0 && d[u] > d[v] + 1) {
				t += (char) (i + 'a');
				DFS2(v);
			}
		}
		for (int i = 0; i < S; i++) {
			int v = c[u][i];
			if (v > 0 && d[u] == d[v] + 1) {
				t += (char) (i + 'a');
				DFS2(v);
			}
		}
		t += '-';
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	Trie t;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		t.insert(s);
	}
	
	t.DFS1(0);
	t.DFS2(0);
	
	string s = t.t;
	while (s.back() == '-') {
		s.pop_back();
	}
	cout << s.size() << "\n";
	for (int i = 0; i < (int) s.size(); i++) {
		cout << s[i] << "\n";
	}
	
	return 0;
}
