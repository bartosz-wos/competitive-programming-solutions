#include <bits/stdc++.h>
using namespace std;

void solve(){
    int a,b;
    cin>>a>>b;
    a*=10,b*=10;
    a=a-a/10;
    if(a<b)
        cout<<"ONLINE\n";
    else if(a>b)
        cout<<"DINING\n";
    else
        cout<<"EITHER\n";
}

int main() {
    int t;
    cin>>t;
    while(t--)solve();
}

