#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T> class OfflineFenwick2D {
  private:
    const int n;
    vector<vector<int>> vals;
    vector<vector<T>> arr;

    int ind(const vector<int> &v, int x) {
        return upper_bound(begin(v), end(v), x) - begin(v) - 1;
    }

  public:
    OfflineFenwick2D(int _n, vector<array<int, 2>> &todo)
        : n(_n), vals(n + 1), arr(n + 1) {
        sort(begin(todo), end(todo), 
            [](const array<int, 2> &a, const array<int, 2> &b) -> bool {
            return a[1] < b[1];
        });
        for (int i = 1; i <= n; i++) { vals[i].push_back(0); }
        for (auto [r, c] : todo) {
            r++, c++;
            for (; r <= n; r += r & -r) {
                if (vals[r].back() != c) { vals[r].push_back(c); }
            }
        }
        for (int i = 1; i <= n; i++) {
            arr[i].resize(vals[i].size());
        }
    }

    /** adds val to the point (r, c) */
    void add(int r, int c, T val) {
        r++, c++;
        for (; r <= n; r += r & -r) {
            int i = ind(vals[r], c);
            for (; i < arr[r].size(); i += i & -i) {
                arr[r][i] += val;
            }
        }
    }

    /** @return rectangle sum for corners (0, 0), (r, c) */
    T rect_sum(int r, int c) {
        r++, c++;
        T sum = 0;
        for (; r > 0; r -= r & -r) {
            int i = ind(vals[r], c);
            for (; i > 0; i -= i & -i) {
                sum += arr[r][i];
            }
        }
        return sum;
    }

    /** @return rectangle sum with corners (r1, c1) and (r2, c2) */
    T rect_sum(int r1, int c1, int r2, int c2) {
        return rect_sum(r2, c2) - rect_sum(r2, c1 - 1) - 
               rect_sum(r1 - 1, c2) + rect_sum(r1 - 1, c1 - 1);
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<array<int, 5>> events;
    vector<int> y_vals;
    for (int i = 0; i < n; i++) {
        int s, t;
        cin >> s >> t;
        events.push_back({0, s, t, s + t, -1});
        y_vals.push_back(t);
    }
    for (int i = 0; i < q; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        events.push_back({1, x, y, z, i});
        y_vals.push_back(y);
    }
    sort(begin(y_vals), end(y_vals));
    y_vals.erase(unique(begin(y_vals), end(y_vals)), end(y_vals));
    vector<array<int, 2>> updates;
    for (auto &[type, a, b, sum, id] : events) {
        b = lower_bound(begin(y_vals), end(y_vals), b) - begin(y_vals);
        if (type == 0) { updates.push_back({b, sum}); }
    }
    sort(begin(events), end(events),
        [](const array<int, 5> &a, const array<int, 5> &b) -> bool {
        return (a[1] == b[1]) ? a[0] < b[0]: a[1] > b[1];
    });
    OfflineFenwick2D<int> ft(y_vals.size(), updates);
    vector<int> res(q);
    for (const auto [type, a, b, sum, id] : events) {
        if (type == 0) {
            ft.add(b, sum, 1);
        } else {
            res[id] = ft.rect_sum(b, sum, y_vals.size() - 1, 2e9);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }
}
