#pragma GCC optimize("O3","inline")
#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(),v.end()
#define ins insert
#define pb push_back
#define int long long
#define pii pair<int,int>
#define endl '\n'
#define drop(x) cout<<(x)<<endl;return;
#define reach cerr<<"reached >.<!"<<endl;
const int mod =  1e9 +7, sze=2e5 +5,inf=LLONG_MAX, prime = 2333;

void gkd(){
    string s;
    cin>>s;
    int ans=0;
    int n=s.length();
    char next = 'H';
    for(int i=0;i<n;i++){
        if(s[i]==next){
            if(s[i]=='I'){
                ans++;
            }
            if(next=='H'){
                next='O';
            }
            else if(next=='O'){
                next='N';
            }
            else if(next=='N'){
                next='I';
            }
            else if(next=='I'){
                next='H';
            }
        }
    }
    drop(ans);
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    int tt=1; 
    // cin>>tt;
    while(tt--) gkd();
    
    return 0;
}
