#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using pl = pair<ll, ll>;
using pi = pair<int, int>;
#define vt vector
#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end() 
#define size(x) ((int) (x).size())
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); i--)
#define F0R(i, b) FOR (i, 0, b)
#define endl '\n'
const ll INF = 1e18;
const int inf = 1e9;
 
template<template<typename> class Container, typename T>
ostream& operator<<(ostream& os, Container<T> o) {
    os << "{"; 
    int g = size(o); 
    for (auto i : o) os << i << ((--g) == 0 ? "" : ", "); 
    os << "}";
    return os;
}
 
void _print() {
    cerr << "\n";
}
 
template<typename T, typename ...V>
void _print(T t, V... v) {
    cerr << t; if (sizeof...(v)) cerr << ", "; _print(v...);
}
 
#ifdef LOCAL
#define dbg(x...) cerr << #x << " = "; _print(x);
#else
#define dbg(x...)
#define cerr if (0) std::cerr
#endif
 
/*
 
isnt this just a greedy wtf
 
*/
 
main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n, m, o; cin >> n >> m >> o; 
    multiset<pl> hotels;
    F0R (i, n) {
        ll c, v; cin >> c >> v;
        hotels.insert({v, c});
    }
    using t3 = tuple<ll, pl, pl>;
    priority_queue<t3> pq;
    ll ans = 0;
    int taken = 0;
    auto add = [&] (ll v, ll c) {
        auto it = hotels.lower_bound({v, -1});
        if (it == hotels.end()) return;
        pq.push({c - it->s, {v, c}, *it});
    };
    F0R (i, m) {
        ll v, c; cin >> c >> v;
        add(v, c);
    }
    while (taken < o) {
        auto [profit, request, hotel] = pq.top(); pq.pop();
        if (profit <= 0) break;
        if (!hotels.count(hotel)) {
            add(request.f, request.s);
        } else {
            hotels.erase(hotels.find(hotel));
            ans += profit;
            taken++;
        }
    }
    cout << ans << endl;
}
