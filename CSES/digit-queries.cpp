#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int main(){
    int t;
    cin>>t;
    while(t--){
        ll x;
        cin>>x;
        x--;
        ll len = 1, num = 1;
        while(x > len*9*num){
            x -= len*9*num;
            len++, num*=10;
        }
        num += x/len;
        x %= len;
        cout<<to_string(num)[x]<<endl;
    }
    return 0;
}
