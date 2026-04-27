#pragma GCC optimize("O3")
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define IOS ios::sync_with_stdio(false); cin.tie(0)
#define ll long long
#define ld long double
#define mp(a, b) make_pair(a, b)
#define pii pair<int, int>
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define fi first
#define se second
 
 
const int N = 2e5 + 10;
const ll LINF = 1e18;
const int INF = 1e9;
const ld PI = 4*atan((ld)1);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
// for n >= 8 solution always exist. there are 7 * bin_coef(8, 2) = 448 dif strings for n = 8
string dp[448];
map<string, string> pr;
vector<string> res;
string s;
 
void precompute(int n) {
    int sz = 0;
    for (int i = 0; i <= n - 2; ++i) {
        string cur = string(i, 'A') + string(n - 2 - i, 'B');
        cur.insert(0, "..");
        dp[sz++] = cur;
        pr[cur] = "";
        if (n < 8) { //if n < 8 parity of dots position does matter
            cur = string(i, 'A') + string(n - 2 - i, 'B');
            cur.insert(1, "..");
            dp[sz++] = cur;
            pr[cur] = "";
        }
    }
 
    int i = 0;
    while(i < sz) {
        string cur = dp[i++];
        int k = cur.find('.');
        for (int i = 0; i < n - 1; ++i) {
            if (cur[i] != '.' && cur[i + 1] != '.') {
                string nxt = cur;
                swap(nxt[i], nxt[k]);
                swap(nxt[i + 1], nxt[k + 1]);
                if (!pr.count(nxt)) {
                    pr[nxt] = cur;
                    dp[sz++] = nxt;
                }
            }
        }
    }
    // for n = 8 sz is 448
}
 
//sort(l, r)
void solve(int l, int r) {
    string cur = s.substr(l, r - l);
    while(pr[cur] != "") {
        cur = pr[cur];
        res.push_back(s.substr(0, l) + cur + s.substr(r));
    }
    s = s.substr(0, l) + cur + s.substr(r);
}
 
void op(int i, int j) { // i + 1 < j && j < 2 * n - 1
    swap(s[i], s[j]);
    swap(s[i + 1], s[j + 1]);
    res.push_back(s);
}
 
int main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }
 
    cin >> s;
    if (n * 2 < 8) {
        precompute(n * 2);
        if (!pr.count(s)) {
            cout << "-1\n";
            return 0;
        }
        solve(0, n * 2);
    }
    else {
        int dots_pos = s.find('.');
        // put dots at the beginning of string
        if (dots_pos > 1) {
            op(dots_pos, 0);
        }
        else if (dots_pos == 1) {
            op(dots_pos, 3);
            op(3, 0);
        }
        dots_pos = 0;
 
        precompute(8);
 
        while(dots_pos + 8 < 2 * n) {
            if (s[dots_pos + 2] == 'A' && s[dots_pos + 3] == 'A') {
                op(dots_pos, dots_pos + 2);
                dots_pos += 2;
            }
            else {
                int b_pos = s.find('B', dots_pos); // bpos <= dots_pos + 1
                int a_pos = s.find('A', b_pos + 2); // apos = 2 * n - 1 is possible
                int flag = 0;
                if (a_pos == s.npos) {
                    solve(dots_pos, dots_pos + 8);
                    break;
                }
                else if (a_pos == 2 * n - 1) { 
                    --a_pos;
                    flag = 1;
                    // s[a_pos, a_pos + 1] == "BA"
                }
 
                op(dots_pos, b_pos);
                op(b_pos, a_pos);
                op(a_pos, dots_pos);
 
 
                if (flag) solve(dots_pos, dots_pos + 8);
            }
        }
        solve(dots_pos, dots_pos + 8);
    }
 
    cout << res.size() << '\n';
    for (auto& x : res) 
        cout << x << '\n';
 
    return 0;
}
