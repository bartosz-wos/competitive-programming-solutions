#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
bool c(ll i,ll j){
    return i>=0 && i<n &&j>=0 && j<m;
}
int main(){
    ll p[5]={};
cin>>n>>m;
char g[n][m];
for(ll i=0;i<n;i++){
    for(ll j=0;j<m;j++){
        cin>>g[i][j];
    }
}
for(ll i=0;i<n;i++){
    for(ll j=0;j<m;j++){
        if(c(i+1,j+1) &&g[i][j] == g[i][j+1] && g[i][j+1] == g[i+1][j] && g[i+1][j] == g[i+1][j+1] && g[i][j]!='.' ){
            p[0]++;
        }
        if(c(i,j+3) &&g[i][j] == g[i][j+1] && g[i][j+1] == g[i][j+2] && g[i][j+2] == g[i][j+3] && g[i][j]!='.'){
            p[1]++;
        }
        if(c(i+3,j) && g[i][j] == g[i+1][j] && g[i+1][j] == g[i+2][j] && g[i+2][j] == g[i+3][j] && g[i][j]!='.'){
            p[1]++;
        }
        if(c(i-1,j+2) && g[i][j]==g[i][j+1] && g[i][j+1]==g[i-1][j+1] && g[i-1][j+1]==g[i-1][j+2] && g[i][j]!='.'){
            p[2]++;
        }
        if(c(i+2,j+1) && g[i][j]==g[i+1][j] && g[i+1][j]==g[i+1][j+1] && g[i+1][j+1]==g[i+2][j+1] && g[i][j]!='.'){
            p[2]++;
        }
        if(c(i+1,j+2) && g[i][j]==g[i][j+1] && g[i][j+1] == g[i+1][j+1] && g[i+1][j+1] == g[i+1][j+2] && g[i][j]!='.'){
            p[3]++;
        }
        if(c(i+2,j-1) && g[i][j]==g[i+1][j] && g[i+1][j] == g[i+1][j-1] && g[i+1][j-1]== g[i+2][j-1] && g[i][j]!='.'){
            p[3]++;
        }
        if(c(i-1,j+2) && g[i][j]==g[i][j+1] && g[i][j+1]==g[i][j+2] && g[i][j]==g[i-1][j+1] && g[i][j]!='.'){
            p[4]++;
        }
        if(c(i+1,j+2) && g[i][j]==g[i][j+1] && g[i][j+1]==g[i][j+2] && g[i][j]==g[i+1][j+1] && g[i][j]!='.'){
            p[4]++;
        }
        if(c(i+2,j+1) && g[i][j]==g[i+1][j] && g[i+1][j]==g[i+2][j] && g[i][j]==g[i+1][j+1] && g[i][j]!='.'){
            p[4]++;
        }
        if(c(i+2,j-1) && g[i][j]==g[i+1][j] && g[i+1][j]==g[i+2][j] && g[i][j]==g[i+1][j-1] && g[i][j]!='.'){
            p[4]++;
        }
    }
}
    for(ll i:p){
        cout<<i<<'\n';
    }
}

