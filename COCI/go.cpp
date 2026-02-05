#include <bits/stdc++.h>
/// #include <ext/pb_ds/assoc_container.hpp>
using namespace std;
/// using namespace __gnu_pbds;
#define int long long
#define pb push_back
#define pii pair<int, int>
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define drop(x) cout<<x<<endl;return
// template <class T>
// using isTree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

/// sometimes you gotta think simple
struct custom_hash {
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        x ^= FIXED_RANDOM;
        return x ^ (x >> 16);
    }
};
void failure()
{
    int n;
    cin >> n;
    int mx = 0;
    int ans = 0;
    string pokemon;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int lazim, var;
        cin >> lazim >> var;
        int cnt = 0;
        while (var >= lazim) {
            cnt++;
            var = var - lazim + 2;
        }
        if (cnt > mx) {
            mx = cnt;
            pokemon = s;
        }
        ans += cnt;
    }
    cout << ans << endl << pokemon << endl;
}
signed main() { 
    ios_base::sync_with_stdio(0); 
    cin.tie(NULL);                
    cout.tie(NULL);
    int tt = 1;
    //cin >> tt;
    while (tt--)
    {
        failure();
    }
}
