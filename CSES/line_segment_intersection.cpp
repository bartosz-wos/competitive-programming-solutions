#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define SUS Point&
 
struct Point {
        ll x, y;
        Point() : x(0), y(0) {}
        Point(ll x, ll y) : x(x), y(y) {}
        void read() {
                cin >> x >> y;
        }
        Point operator +(const Point& b) const {
                return {x + b.x, y + b.y};
        }
        Point operator -(const Point& b) const {
                return {x - b.x, y - b.y};
        }
        ll operator*(const Point& b) const {
                return x * b.y - b.x * y;
        }
        ll cross(const Point& b, const Point& c) {
                return (b - *this) * (c - *this);
        }
};
 
ll sgn(ll x) {
        if(x > 0)
                return 1;
        if(x < 0)
                return -1;
        return 0;
}
 
bool inter1(ll a, ll b, ll c, ll d) {
        if(a > b)
                swap(a, b);
        if(c > d)
                swap(c, d);
        return max(a, c) <= min(b, d);
}
 
bool check_inter(SUS a, SUS b, SUS c, SUS d) {
        if(c.cross(a, d) == 0 and c.cross(b, d) == 0)
                return inter1(a.x, b.x, c.x, d.x) and inter1(a.y, b.y, c.y, d.y);
        return sgn(a.cross(b, c)) != sgn(a.cross(b, d)) and sgn(c.cross(d, a)) != sgn(c.cross(d, b));
}
 
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int q;
        cin >> q;
        Point P[4];
        while(q--) {
                for(int i = 0; i < 4; ++i)
                        P[i].read();
                cout << (check_inter(P[0], P[1], P[2], P[3]) ? "YES\n" : "NO\n");
        }
}
