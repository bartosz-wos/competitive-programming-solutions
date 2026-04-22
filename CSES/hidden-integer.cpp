#include <bits/stdc++.h>
using namespace std;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int64_t lo = 1, hi = 1000000000;
    while(lo < hi){
        int64_t mid = lo + (hi - lo) / 2;
        cout << "? " << mid << "\n" << flush;
        string resp;
        cin >> resp;
        if(!cin) 
            return 0;
        if(resp == "YES"){
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    cout << "! " << lo << "\n" << flush;
    return 0;
}
