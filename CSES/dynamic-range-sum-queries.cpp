#include <iostream>
using namespace std;
using ll = long long;
constexpr int poz = 20;
constexpr int u = 1 << (poz - 1);
 
ll T[1 << poz];
 
void act(int index, int value) {
    index += u;
    value -= T[index];
    T[index] += value;
    index >>= 1;
    while(index) {
        T[index] += value;
        index >>= 1;
    }
}
 
ll query(int a, int b) {
    a = a + u - 2;
    b = b + u;
 
    ll odp = 0;
 
    while(b - a > 1) {
        if( !(a & 1) )
            odp += T[a + 1];
        if( b & 1 )
            odp += T[b - 1];
        a >>= 1;
        b >>= 1;
    }
 
    return odp;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q, p, a, b, z;
    cin >> n >> q;
 
    for(int i = 0; i < n; ++i)
        cin >> T[i+u];
    for(int i = u - 1; i > 0; --i)
        T[i] = T[i << 1] + T[(i << 1) + 1];
 
    while(q--) {
        cin >> z >> a >> b;
        if(z == 2)
            cout << query(a, b) << '\n';
        else
            act(a - 1, b);
    }
}
