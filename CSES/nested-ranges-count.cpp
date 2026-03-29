#include<iostream>
#include<algorithm>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pi = pair<int, int>;
 
struct range {
    int l, r, index;
    bool operator <(const range& other) const {
        if(l == other.l)
            return r > other.r;
        return l < other.l;
    }
} tab[200007];
 
int n, contains[200007], contained[200007];
ordered_set<pi> S;
int main() {
    ios;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> tab[i].l >> tab[i].r;
        tab[i].index = i;
    }
    sort(tab, tab + n);
    for(int i = n - 1; i >= 0; --i) {
        S.insert( {tab[i].r, -i} );
        contains[tab[i].index] = S.order_of_key( {tab[i].r, -i} );
    }
    S.clear();
    for(int i = 0; i < n; ++i) {
        S.insert({tab[i].r, -i});
        contained[tab[i].index] = S.size() - S.order_of_key({tab[i].r, -i}) - 1;
    }
    for(int i = 0; i < n; ++i)
        cout << contains[i] << ' ';
    cout << '\n';
    for(int i = 0; i < n; ++i)
        cout << contained[i] << ' ';
}
