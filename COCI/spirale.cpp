#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << #x << ": " << x << endl;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m, -1));
    int cnt_used = 0;
    vector<tuple<int, int, int>> spirals(k);
    for (auto& [x, y, dir] : spirals) {
        cin >> x >> y >> dir;
        --x, --y;
    }
    // 1 - up, 2 - down, 3 - left, 4 - right
    vector<set<pair<int, int>>> used_cells(k);
    vector<vector<int>> nxt(2, vector<int>(5));
    vector<pair<int, int>> moves(5);
    moves[1] = {-1, 0};
    moves[2] = {1, 0};
    moves[3] = {0, -1};
    moves[4] = {0, 1};
    nxt[1] = {1, 3, 4, 2, 1};
    nxt[0] = {1, 4, 3, 1, 2};
    vector<int> last_step(k);
    for (int step = 1; step <= 10000; ++step) {
        if (cnt_used >= n * m) break;
        int i = 0;
        for (auto& [x, y, dir] : spirals) {
            if (x >= 0 && x < n && y >= 0 && y < m) {
                if (a[x][y] == -1) {
                    ++cnt_used;
                    a[x][y] = step;
                }
            }
            used_cells[i].emplace(x, y);
            auto [dx, dy] = moves[nxt[dir][last_step[i]]];
            if (used_cells[i].count({x + dx, y + dy})) {
                auto [dx2, dy2] = moves[last_step[i]];
                x += dx2;
                y += dy2;
            } else {
                x += dx;
                y += dy;
                last_step[i] = nxt[dir][last_step[i]];
            }
            ++i;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}

