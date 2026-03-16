#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fast                       \
 ios_base::sync_with_stdio(0);      \
 cin.tie(0);                         \
 cout.tie(0);
 
int main(){
    fast;
    ll t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<vector<int>> v(n,vector<int>(n));
        for(int i=0;i<n;i++){
            int ind=(2*i)%n;
            for(int j=0;j<n;j++){
                v[i][(ind-j+n)%n]=j;
            }
        }
        for(auto i:v){
            for(auto j:i) cout<<j+1<<" ";
            cout<<"\n";
        }
    }
}
