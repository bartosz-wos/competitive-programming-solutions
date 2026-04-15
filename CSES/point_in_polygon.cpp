#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int MAXN=1005;
 
struct Point{
    ll x,y;
    Point():x(0),y(0){}
    Point(ll x, ll y):x(x),y(y){}
    void read(){cin>>x>>y;}
    Point operator+(const Point&b)const{
        return Point(x+b.x,y+b.y);
    }
    Point operator-(const Point&b)const{
        return Point(x-b.x,y-b.y);
    }
    ll operator*(const Point&b)const{
        return x*b.y-b.x*y;
    }
    void operator+=(const Point&b){
        x+=b.x,y+=b.y;
    }
    void operator-=(const Point&b){
        x-=b.x,y-=b.y;
    }
    void operator*=(const ll&k){
        x*=k,y*=k;
    }
    ll cross(const Point&b, const Point&c)const{
        return (b-*this)*(c-*this);
    }
};
 
int n,m;
Point P[MAXN];
 
bool PL(Point P1, Point P2, Point P3){
    if(P2.cross(P1,P3)!=0)return 0;
    return min(P2.x, P3.x) <= P1.x && P1.x <= max(P2.x, P3.x)
        && min(P2.y, P3.y) <= P1.y && P1.y <= max(P2.y, P3.y);
}
 
void check(){
    int cnt=0;
    bool boundary=0;
    for(int i=1;i<=n;++i){
        int j=(i==n?1:i+1);
        if(PL(P[0],P[i],P[j])){
            boundary=1;
            break;
        }
        if(P[i].x<=P[0].x  and P[0].x<P[j].x and P[0].cross(P[i],P[j])<0)++cnt;
        else if(P[j].x<=P[0].x and P[0].x<P[i].x and P[0].cross(P[j],P[i])<0)++cnt;
    }
    if(boundary)cout<<"BOUNDARY\n";
    else if(cnt&1)cout<<"INSIDE\n";
    else cout<<"OUTSIDE\n";
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i)P[i].read();
    while(m--){
        P[0].read();
        check();
    }
}
