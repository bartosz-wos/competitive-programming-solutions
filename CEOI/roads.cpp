#include <bits/stdc++.h>
using namespace std;

constexpr size_t N = 100001;
constexpr int32_t X = 100000000;
int32_t x;

struct segment
{
    int32_t x1, y1, x2, y2, rx, ry;
    double get_y() const { return x1 == x2 ? y1 : y1 + (double)(y2 - y1) / (x2 - x1) * (x - x1); }
    bool operator<(segment const &s) const { return get_y() < s.get_y(); }
};

segment s[N];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    size_t n;
    cin >> n;
    vector<tuple<int32_t, int32_t, int32_t, int32_t>> e;
    for (size_t i = 0; i < n; ++i)
    {
        cin >> s[i].x1 >> s[i].y1 >> s[i].x2 >> s[i].y2;
        if (s[i].x2 < s[i].x1 || (s[i].x1 == s[i].x2 && s[i].y2 < s[i].y1))
            swap(s[i].x1, s[i].x2), swap(s[i].y1, s[i].y2);
        e.emplace_back(s[i].x1, s[i].y1, 0, i);
        e.emplace_back(s[i].x2, s[i].y2, 1, i);
    }

    sort(e.begin(), e.end());
    auto compare_segment = [](auto const &a, auto const &b)
    { return s[a] < s[b]; };
    set<int32_t, decltype(compare_segment)> t(compare_segment);
    s[n] = (segment){-X, -X, X, -X, -X, -X};
    t.insert(n);
    for (auto const &[_x, _y, type, i] : e)
    {
        x = _x;
        if (!type)
        {
            auto it = --t.lower_bound(i);
            if (s[*it].rx != -X)
                cout << s[*it].rx << ' ' << s[*it].ry << ' ' << s[i].x1 << ' ' << s[i].y1 << '\n';
            s[*it].rx = s[i].x1, s[*it].ry = s[i].y1;
            it = t.insert(i).first;
            s[*it].rx = s[i].x1, s[*it].ry = s[i].y1;
        }
        else
        {
            auto it = t.find(i);
            it = --t.erase(it);
            s[*it].rx = s[i].x2, s[*it].ry = s[i].y2;
        }
    }
}
