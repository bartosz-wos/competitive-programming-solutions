#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
struct Point {
    int x, y;
    void read(){ cin >> x >> y; }
    Point operator +(const Point& b) const { return Point{x+b.x, y+b.y}; }
    Point operator -(const Point& b) const { return Point{x-b.x, y-b.y}; }
    ll operator *(const Point& b) const { return (ll) x * b.y - (ll) y * b.x; }
    void operator +=(const Point& b) { x += b.x; y += b.y; }
    void operator -=(const Point &b) { x -= b.x; y -= b.y; }
    void operator *=(const int k) { x *= k; y *= k; }
    ll cross(const Point& b, const Point& c) const {
        return (b - *this) * (c - *this);
    }
};
 
int T;
Point P[3];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> T;
    for(int t = 0; t < T; t++){
        for(int i = 0; i < 3; i++)
            P[i].read();
 
        ll cross = P[0].cross(P[1], P[2]);
        if(cross < 0)       cout <<"RIGHT\n";
        else if(cross > 0)  cout <<"LEFT\n";
        else                cout <<"TOUCH\n";
    }
}
