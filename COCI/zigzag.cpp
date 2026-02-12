#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    int k, n;
    cin >> k >> n;
    vector<priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>>> v(26);
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        v[s[0]-'a'].push({0, s});
    }
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        cout << v[c-'a'].top().second << '\n';
        pair<int, string> x = v[c-'a'].top();
        v[c-'a'].pop();
        x.first++;
        v[c-'a'].push(x);
    }
    return 0;
}
