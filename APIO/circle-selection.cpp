#include <bits/stdc++.h>
#define all(dataStructure) dataStructure.begin(),dataStructure.end()

using namespace std;

typedef long long ll;

const int MAX = 3e5 + 3;
const ll MOD[] = {1000000007, 998244353};

int n, blockSize = 2e9;
int ans[MAX];
int x[MAX], y[MAX], r[MAX];

set <int> S;
map <pair <int, int>, vector <int>> block;

ll sq(ll x) {
        return x * x;
}

ll dist(int i, int j) {
        return sq(x[i] - x[j]) + sq(y[i] - y[j]);
}

void rebuild() {
        block.clear();
        for (auto &&i : S) block[{x[i] / blockSize, y[i] / blockSize}].push_back(i);
}

void Solve() {
        cin >> n;
        vector <int> id(n);
        for (int i = 1; i <= n; i++) {
                S.insert(i);
                cin >> x[i] >> y[i] >> r[i];
        }

        iota(all(id), 1);
        sort(all(id), [&](const int &i, const int &j) {
                if (r[i] != r[j]) return r[i] > r[j];
                return i < j;
        });

        for (int &i : id) {
                if (ans[i]) continue;
                if (r[i] * 2 <= blockSize) {
                        blockSize = r[i];
                        rebuild();
                }

                for (int x = ::x[i] / blockSize - 2; x <= ::x[i] / blockSize + 2; x++) {
                        for (int y = ::y[i] / blockSize - 2; y <= ::y[i] / blockSize + 2; y++) {
                                if (!block.count({x, y})) continue;
                                for (int &j : block[{x, y}]) if (!ans[j]) {
                                        if (dist(i, j) <= sq(r[i] + r[j])) {
                                                ans[j] = i;
                                                S.erase(j);
                                        }
                                }
                        }
                }
        }

        for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
}

int32_t main() {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0); std::cout.tie(0);

        #define TASK ""
        if (fopen(TASK".INP", "r")) {
                freopen(TASK".INP", "r", stdin);
                freopen(TASK".OUT", "w", stdout);
        }

        if (fopen("TASK.INP", "r")) {
                freopen("TASK.INP", "r", stdin);
                freopen("TASK.OUT", "w", stdout);
        }

        /* int TEST = 1; cin >> TEST; while (TEST--) */ Solve();

        cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << "s\n";
        return 0;
}
