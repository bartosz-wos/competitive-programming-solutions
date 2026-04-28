#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
ll knight_to_11(ll x, ll y){
    ll dx = llabs(x - 1), dy = llabs(y - 1);
    if(dx < dy) swap(dx, dy);
 
    if(dx == 0 && dy == 0) return 0;
    if(dx == 1 && dy == 0) return 3;
    if(dx == 1 && dy == 1) return 4;
    if(dx == 2 && dy == 2) return 4;
 
    ll d1 = (dx + 1) / 2;
    ll d2 = (dx + dy + 2) / 3;
    ll d  = max(d1, d2);
 
    if ((d & 1) != ((dx + dy) & 1)) 
        d++;
 
    return d;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int Q;
    cin >> Q;
    while(Q--){
        ll x,y;
        cin >> x >> y;
        cout << knight_to_11(x,y) << "\n";
    }
}
