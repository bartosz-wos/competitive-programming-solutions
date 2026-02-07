#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    vector<long long> sum(b+1);
    for (int i = 2; i <= b; i++) {
        for (int j = i+i; j <= b; j += i) sum[j] += i;
        sum[i]++;
    }
    long long ans = 0;
    for (int i = a; i <= b; i++) ans += abs(i-sum[i]);
    cout << ans << '\n';
    return 0;
}
