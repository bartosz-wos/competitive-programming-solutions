#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int find_lis(const vector<int> &a) {
    vector<int> dp;
    for (int i : a) {
        int pos = std::upper_bound(dp.begin(), dp.end(), i) - dp.begin();
        if (pos == dp.size()) {
            dp.push_back(i);
        } else {
            dp[pos] = i;
        }
    }
    return dp.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int len;
    int block_size;
    cin >> len >> block_size;
    vector<pair<int, int>> arr(len);
    for (int i = 0; i < len; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr.begin(), arr.end());

    vector<int> block_arr(len);
    for (int i = 0; i < arr.size(); i++) { block_arr[arr[i].second] = i / block_size; }
    cout << len - find_lis(block_arr) << '\n';
}
