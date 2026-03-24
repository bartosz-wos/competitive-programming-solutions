#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j)
            cout<<(i^j)<<' ';
        cout<<'\n';
    }

