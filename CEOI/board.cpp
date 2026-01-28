#include <bits/stdc++.h>
using namespace std;

vector<int> get(const string &s)
{
    vector<int> v;
    for (const char &c : s)
    {
        if (c == '1') v.push_back(0);
        if (c == '2') v.push_back(1);
        if (c == 'L') v.back()--;
        if (c == 'R') v.back()++;
        if (c == 'U')
        {
            int val = v.back(); v.pop_back();
            v.back() += (val >> 1);
        }
    }
    for (int i = v.size() - 1; i > 0; i--)
    {
        int val = v[i] >> 1;
        v[i] -= (val << 1);
        v[i - 1] += val;
    }
    return v;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); 
    string sa, sb;
    cin >> sa >> sb;
    vector<int> a = get(sa), b = get(sb);
    int dif = 0, dist = a.size() + b.size(), ans = dist;
    for (int i = 0; i < min(a.size(), b.size()); i++)
    {
        dist -= 2;
        dif <<= 1, dif += a[i] - b[i];
        int val = dist + abs(dif);
        if (val > 1e6) break;
        ans = min(ans, val);
    }
    cout << ans << "\n";
    return 0;
}
