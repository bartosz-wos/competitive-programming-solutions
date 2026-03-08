#include<bits/stdc++.h>
using std::cout;
using std::endl;
using std::vector;

const int MAX_VAL = 100;
const int MAX_POSS = 2 * 5e3;

const vector<int> PRIMES = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                            43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

class PrimeLog {
  private:
    vector<vector<int>> rel_factors;

  public:
    PrimeLog(int n) : rel_factors(n + 1) {
        for (int i = 2; i <= n; i++) {
            for (int p : PRIMES) {
                if (i % p == 0) { rel_factors[i].push_back(p); }
            }
        }
    }

    const vector<int> &get_factors(int n) { return rel_factors[n]; }
} factors(MAX_POSS);

class GCDTree {
  private:
    const vector<vector<int>> &neighbors;
    const vector<int> &vals;
    vector<vector<int>> min_cost;
    vector<std::map<int, int>> factor_best;

    void dfs(int at, int prev) {
        min_cost[at] = vector<int>(MAX_POSS + 1);
        for (int i = 2; i <= MAX_POSS; i++) {
            if (i != vals[at]) { min_cost[at][i] = i; }
            if (factors.get_factors(i).empty()) { min_cost[at][i] = INT32_MAX; }
        }

        for (int n : neighbors[at]) {
            if (n == prev) { continue; }

            dfs(n, at);
            for (int i = 2; i <= MAX_POSS; i++) {
                if (factors.get_factors(i).empty()) { continue; }
                int n_min_cost = INT32_MAX;
                for (int p : factors.get_factors(i)) {
                    n_min_cost = std::min(n_min_cost, factor_best[n][p]);
                }
                min_cost[at][i] += n_min_cost;
            }
        }

        for (int p : PRIMES) {
            int p_best = INT32_MAX;
            for (int i = p; i <= MAX_POSS; i += p) {
                p_best = std::min(p_best, min_cost[at][i]);
            }
            factor_best[at][p] = p_best;
        }
    }

  public:
    GCDTree(const vector<vector<int>> &neighbors, const vector<int> &vals)
        : neighbors(neighbors), vals(vals), min_cost(neighbors.size()),
          factor_best(neighbors.size()) {
        dfs(0, 0);
    }

    int min_adjustment() const {
        int res = INT32_MAX;
        for (int i = 2; i <= MAX_POSS; i++) { res = std::min(res, min_cost[0][i]); }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int node_num;
    std::cin >> node_num;
    vector<int> vals(node_num);
    for (int &v : vals) { std::cin >> v; }
    vector<vector<int>> neighbors(node_num);
    for (int i = 0; i < node_num - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        neighbors[--a].push_back(--b);
        neighbors[b].push_back(a);
    }

    cout << GCDTree(neighbors, vals).min_adjustment() << endl;
}
