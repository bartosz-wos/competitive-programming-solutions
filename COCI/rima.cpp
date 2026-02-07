#include "bits/stdc++.h"

using namespace std;

#define ln "\n"
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
// #define int long long
const int MOD = 1e9 + 7;
const int inf = 2e9;
const int N = 3e6 + 7;

struct Trie {
    struct Node {
        Node * child[26];
        int cnt;
        Node() {
            for(int i = 0; i < 26; i++) child[i] = NULL;
            cnt = 0;
        }
    };
    int ans;
    Node* root;
    Trie(){
        root = new Node();
    };
    void add(string s) {
        Node * p = root;
        for(char c: s) {
            int i = c - 'a';
            if(p->child[i] == NULL) p->child[i] = new Node();
            p = p->child[i];
        }
        p->cnt = 1;
    }
    int dfs(Node * p) {
        int ans1 = 0, ans2 = 0;
        int sus = 0;
        int cnt = 0;
        for(int i = 0; i < 26; i++) {
            if(p->child[i] == NULL) continue;
            Node * v = p->child[i];
            int x = dfs(v);
            if(v->cnt) {
                cnt++;
                if(x >= ans1) {
                    ans2 = ans1;
                    ans1 = x;
                } else if(x > ans2) {
                    ans2 = x;
                }
            }
        }
        sus = p->cnt;
        if(cnt) {
            sus += cnt - 1 + ans1;
        }
        ans = max(ans, sus);
        if(cnt > 1) {
            ans = max(ans, ans1 + ans2 + cnt - 2 + p->cnt);
        }
        return sus;
    }
} tri;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
   // if(fopen("rima.inp", "r")) {
   //     freopen("rima.inp", "r", stdin);
   // }
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        string s; cin >> s;
        reverse(all(s));
        tri.add(s);
    }
    tri.dfs(tri.root);
    cout << tri.ans;
}
