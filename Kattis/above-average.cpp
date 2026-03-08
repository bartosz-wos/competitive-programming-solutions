#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

void solve(){
    int n;
    cin>>n;
    vector<ld>a(n);
    ld med=0;
    for(auto&x:a){
        cin>>x;
        med+=x;
    }
    med/=(ld)n;
    ld cnt=0;
    for(auto&x:a){
        if((ld)x>med)++cnt;
    }
    cout<<100.0*(ld)cnt/(ld)n<<"%\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout<<fixed<<setprecision(3);
    int t;
    cin>>t;
    while(t--)
        solve();
}
