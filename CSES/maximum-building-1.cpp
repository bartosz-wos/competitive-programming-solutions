#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int grid[1001][1001];
int d[1001],d1[1001],d2[1001];
int n,m;
 
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        string s;
        cin>>s;
        for(int j=1;j<=m;++j)
            if(s[j-1]=='*')
                grid[i][j]=1;
    }
    int res=0;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j)
            if(grid[i][j])
                d[j]=i;
        stack<int>S1;
        for(int j=1;j<=m;++j){
            while(!S1.empty() and d[S1.top()]<=d[j])
                S1.pop();
            d1[j]=(S1.empty()?0:S1.top());
            S1.push(j);
        }
        stack<int>S2;
        for(int j=m;j>=1;--j){
            while(!S2.empty() and d[S2.top()]<=d[j])
                S2.pop();
            d2[j]=(S2.empty()?(m+1):S2.top());
            S2.push(j);
        }
        for(int j=1;j<=m;++j)
            if(!grid[i][j])
                res=max(res,(i-d[j])*(d2[j]-d1[j]-1));
    }
    cout<<res;
}
