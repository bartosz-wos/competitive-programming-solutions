#include<bits/stdc++.h>
using namespace std;
using ll=long long;

static const int MAX_N = 1000;
static const int MAX_Q = 2000;

int n[2], m[2];
vector<int> g[2][MAX_N + 1];
vector<int> back[2][MAX_N + 1];
bitset<MAX_Q + 1> dp[2][MAX_N + 1];

void gen(int x) {
    int in_degree[MAX_N + 1] = {};
    for (int i = 0; i < m[x]; i++) {
        int a, b;
        cin >> a >> b;
        g[x][a].push_back(b);
        back[x][b].push_back(a);
        in_degree[b]++;
    }
    queue<int> q;
    for (int i = 0; i <= n[x]; i++) {
        if (in_degree[i] == 0) { q.push(i); }
    }
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next : g[x][node]) {
            in_degree[next]--;
            if (in_degree[next] == 0) { q.push(next); }
        }
        if (back[x][node].empty()) { dp[x][node][0] = 1; }
        for (int before : back[x][node]) { dp[x][node] |= dp[x][before] << 1; }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n[0] >> n[1] >> m[0] >> m[1];

    gen(0);
    gen(1);

    bitset<MAX_Q + 1> ans;
    for (int i = 0; i <= MAX_N; i++) {
        if (dp[0][n[0]][i]) { ans |= dp[1][n[1]] << i; }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a;
        cin >> a;
        cout << ((ans[a]) ? "Yes\n" : "No\n");
    }
    return 0;
}
