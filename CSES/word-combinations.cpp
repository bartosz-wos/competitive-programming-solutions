#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
ll dp[5001];
 
struct trie {
	bool leaf;
	trie* child[26];
};
 
trie* create() {
	trie* temp = new trie();
	temp->leaf = 0;
	for(int i = 0; i < 26; ++i)
		temp->child[i] = nullptr;
	return temp;
}
 
void insert(trie* root, const string& s) {
	for(int i = 0; i < s.length(); ++i) {
		if(root->child[s[i] - 97] == nullptr)
			root->child[s[i] - 97] = create();
		root = root->child[s[i] - 97];
	}
	root->leaf = 1;
}
 
string txt;
int t;
ll ans = 0;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	trie* root = create();
	cin >> txt;
	cin >> t;
	while(t--) {
		string  a;
		cin >> a;
		insert(root, a);
	}
	dp[txt.length()] = 1;
	for(int i = txt.length() - 1; i >= 0; --i) {
		trie* node = root;
		for(int j = i; j < txt.length(); ++j) {
			if(node->child[txt[j] - 97] == nullptr)
				break;
			node = node->child[txt[j] - 97];
			if(node->leaf)
				dp[i] = (dp[i] + dp[j+1]) % mod;
		}
	}
	cout << dp[0];
}
