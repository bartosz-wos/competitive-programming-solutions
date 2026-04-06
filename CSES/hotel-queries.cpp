#include<bits/stdc++.h>
using namespace std;
constexpr int poz = 20, u = 1 << (poz - 1);
int n, m, p, T[u << 1];
 
void odejmij(int index, int val) {
    index += u - 1;
    T[index] -= val;
    index >>= 1;
    while(index)
        T[index] = max(T[index << 1], T[(index << 1) + 1]), index >>= 1;
}
 
int segmax(int a, int b) {
    a += u - 2;
    b += u;
    int ans = 0;
    while(b - a > 1) {
        if(!(a & 1))
            ans = max(ans, T[a+1]);
        if(b & 1)
            ans = max(ans, T[b-1]);
        a >>= 1;
        b >>= 1;
    }
    return ans;
}
 
int bin_search(int val) {
    int l = 1, r = n, mid = 0, ans = -1;
 
    while(l <= r) {
        mid = (l + r) >> 1;
        if(segmax(1, mid) >= val) {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    for(int i = 0; i < n; ++i)
        cin >> T[u+i];
    for(int i = u - 1; i; --i)
        T[i] = max( T[i << 1], T[(i << 1) + 1] );
 
    while(m--) {
        cin >> p;
        int q = bin_search(p);
        if(q == -1) {
            cout << 0 << ' ';
            continue;
        }
        cout << q << ' ';
        odejmij(q, p);
    }
}
