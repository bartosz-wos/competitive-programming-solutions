#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int LIM=1e8;
 
int t[LIM+5];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    t[1]=1;
    for(int i=2;i<=LIM;++i){
        --t[i];
        for(int j=2*i;j<=LIM;j+=i)
            t[j]-=t[i];
        if(t[i]==-1)t[i]=1;
        t[i]+=t[i-1];
    }
    while(1){
        int a,b;
        cin>>a>>b;
        if(!a and !b)break;
        cout<<b-a+1-t[b]+t[a-1]<<'\n';
    }
}
