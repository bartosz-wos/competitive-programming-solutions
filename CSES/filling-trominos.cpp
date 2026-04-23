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
 
int a[100][100];
char b[100][100];
int c[9][5] = {
        { 0, 0, 7, 4, 4}, // 0
        { 0, 7, 7,13, 4}, // 5
        {10,10,13,13,19}, //10 
        {10,17,17,19,19}, //15
        {20,20,17,24,24}, //20
        {20,27,27,33,24}, //25
        {30,30,27,33,33}, //30
        {30,41,42,39,39}, //35
        {41,41,42,42,39}, //40
};
 
bool is_solvable(int n, int m) {
    if (n * m % 3)
        return false;
    if (min(n, m) == 1)
        return false;
    if (n % 3 != 0 && m % 3 == 0)
        swap(n, m);
    if (n % 3 == 0 && m % 3 == 0 && m < n)
        swap(n, m);
 
    if (n * m % 2 == 0)
        return true;
    if (n == 3)
        return false;
    return true;
}
 
int solve(int n, int m) {
    int is_trans = 0;
    if (n % 3 != 0 && m % 3 == 0) {
        swap(n, m);
        is_trans = 1;
    }
    if (n % 3 == 0 && m % 3 == 0 && m < n && !(n % 6 == 0 && m % 6 != 0)) {
        swap(n, m);
        is_trans = 1;
    }
    if (n % 3 == 0 && m % 2 == 0) {
        for (int i = 0; i < n; i += 3) 
            for (int j = 0; j < m; j += 2) {
                a[i][j] = a[i + 1][j] = a[i][j + 1] = i * m + j;
                a[i + 2][j + 1] = a[i + 1][j + 1] = a[i + 2][j] = (i + 2) * m + (j + 1);
            }
    }
    else if (n % 6 == 0) {
        // m % 2 == 1 should be
        for (int i = 0; i < n; i += 3) 
            for (int j = 0; j + 3 < m; j += 2) {
                a[i][j] = a[i + 1][j] = a[i][j + 1] = i * m + j;
                a[i + 2][j + 1] = a[i + 1][j + 1] = a[i + 2][j] = (i + 2) * m + (j + 1);
            }
        for (int i = 0; i < n; i += 2) {
            a[i][m - 3] = a[i][m - 2] = a[i + 1][m - 3] = i * m + m - 3;
            a[i + 1][m - 1] = a[i][m - 1] = a[i + 1][m - 2] = i * m + m - 1;
        }
    }
    else {
        // n >= 9, n % 3 == 0, n % 2 != 0, m % 2 != 0
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 5; ++j)
                a[i][j] = c[i][j];
 
 
        for (int i = 9; i < n; i += 3) 
            for (int j = 0; j + 3 < 5; j += 2) {
                a[i][j] = a[i + 1][j] = a[i][j + 1] = i * m + j;
                a[i + 2][j + 1] = a[i + 1][j + 1] = a[i + 2][j] = (i + 2) * m + (j + 1);
            }
        for (int i = 9; i < n; i += 2) {
            a[i][5 - 3] = a[i][5 - 2] = a[i + 1][5 - 3] = i * m + 5 - 3;
            a[i + 1][5 - 1] = a[i][5 - 1] = a[i + 1][5 - 2] = i * m + 5 - 1;
        }
 
        for (int i = 0; i < n; i += 3) 
            for (int j = 5; j < m; j += 2) {
                a[i][j] = a[i + 1][j] = a[i][j + 1] = i * m + j;
                a[i + 2][j + 1] = a[i + 1][j + 1] = a[i + 2][j] = (i + 2) * m + (j + 1);
            }
 
    }
 
    return is_trans;
}
 
int main() {
    IOS;
 
    int t;
    cin >> t;
    vector<int> g[10000];
    char color[10000];
    memset(color, 0, sizeof(color));
 
    while(t--) {
        int n, m;
        cin >> n >> m;
        if (!is_solvable(n, m)) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
        int is_trans = solve(n, m);
        if (is_trans) swap(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j + 1 < m; ++j) 
                if (a[i][j] != a[i][j + 1]) {
                    g[a[i][j]].push_back(a[i][j + 1]);
                    g[a[i][j + 1]].push_back(a[i][j]);
                }
        for (int i = 0; i + 1 < n; ++i)
            for (int j = 0; j < m; ++j) 
                if (a[i + 1][j] != a[i][j]) {
                    g[a[i][j]].push_back(a[i + 1][j]);
                    g[a[i + 1][j]].push_back(a[i][j]);
                }
 
        for (int i = 0; i < n * m; ++i) {
            if (g[i].empty()) continue;
 
            int used[26];
            memset(used, 0, sizeof(used));
            for (auto u : g[i]) {
                if (color[u])
                    used[color[u] - 'A'] = 1;
            }
            for (int j = 0; j < 26; ++j) {
                if (!used[j]) {
                    color[i] = char(j + 'A');
                    break;
                }
            }
 
            g[i].clear();
        }
        if (!is_trans) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    cout << color[a[i][j]];
                }
                cout << '\n';
            }
        }
        else {
            for (int j = 0; j < m; ++j) {
                for (int i = 0; i < n; ++i) {
                    cout << color[a[i][j]];
                }
                cout << '\n';
            }
        }
        memset(color, 0, sizeof(color));
    }
 
    return 0;
}
