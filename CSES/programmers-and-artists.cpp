#include <bits/stdc++.h>
using namespace std;
 
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif
 
template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}
 
template<typename T>
struct FastSet {
    priority_queue<T> pq, pending;
 
    void add(T x) {
        pq.push(x);
    }
 
    void rem(T x) {
        pending.push(x);
        while (!pq.empty() && !pending.empty() && pq.top() == pending.top()) {
            pq.pop();
            pending.pop();
        }
    }
 
    T max() {
        assert(!pq.empty());
        return pq.top();
    }
};
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int a, b, n;
    cin >> a >> b >> n;
    vector<int> x(n), y(n);
    for (int i=0; i<n; i++)
        cin >> x[i] >> y[i];
 
    FastSet<pair<int, int>> pqA, pqB;
    priority_queue<pair<int, int>> pqA2, pqB2;
    for (int i=0; i<n; i++) {
        pqA.add({x[i], i});
        pqB.add({y[i], i});
    }
 
    long long ret = 0;
    while (a > 0 || b > 0) {
        int mx = 0;
        if (a > 0) {
            if (!pqA.pq.empty())
                mx = max(mx, pqA.max().first);
            if (!pqB.pq.empty() && !pqB2.empty())
                mx = max(mx, pqB.max().first + pqB2.top().first);
        }
        if (b > 0) {
            if (!pqB.pq.empty())
                mx = max(mx, pqB.max().first);
            if (!pqA.pq.empty() && !pqA2.empty())
                mx = max(mx, pqA.max().first + pqA2.top().first);
        }
        assert(mx > 0);
 
        ret += mx;
        if (a > 0) {
            if (!pqA.pq.empty() && mx == pqA.max().first) {
                int i = pqA.max().second;
                pqA.rem({x[i], i});
                pqB.rem({y[i], i});
                pqA2.emplace(y[i] - x[i], i);
                a--;
                continue;
            }
            if (!pqB.pq.empty() && !pqB2.empty() && mx == pqB.max().first + pqB2.top().first) {
                int i = pqB.max().second, j = pqB2.top().second;
                pqA.rem({x[i], i});
                pqB.rem({y[i], i});
                pqB2.pop();
                pqB2.emplace(x[i] - y[i], i);
                pqA2.emplace(y[j] - x[j], j);
                a--;
                continue;
            }
        }
        if (b > 0) {
            if (!pqB.pq.empty() && mx == pqB.max().first) {
                int i = pqB.max().second;
                pqA.rem({x[i], i});
                pqB.rem({y[i], i});
                pqB2.emplace(x[i] - y[i], i);
                b--;
                continue;
            }
            if (!pqA.pq.empty() && !pqA2.empty() && mx == pqA.max().first + pqA2.top().first) {
                int i = pqA.max().second, j = pqA2.top().second;
                pqA.rem({x[i], i});
                pqB.rem({y[i], i});
                pqA2.pop();
                pqA2.emplace(y[i] - x[i], i);
                pqB2.emplace(x[j] - y[j], j);
                b--;
                continue;
            }
        }
        assert(false);
    }
 
    cout << ret << "\n";
 
    return 0;
}
