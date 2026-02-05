#include <bits/stdc++.h>
using namespace std;
int n;
vector <int> nums;
int main() {
    cin >> n;
    nums.resize(n);
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    int ans = 0;
    int l = 0, r = n-1;
    int suml = nums[0], sumr = nums[n-1];
    while (l < r) {
        if (suml == sumr) {
            suml = nums[l+1];
            sumr = nums[r-1];
            l++;
            r--;
        } else if (suml < sumr) {
            suml += nums[l+1];
            ans++;
            l++;
        } else {
            sumr += nums[r-1];
            ans++;
            r--;
        }
    }
    cout << ans << '\n';
}
