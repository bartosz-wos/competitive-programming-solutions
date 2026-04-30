#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,a[2][100005];
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=0;i<2;++i)
        for(int j=0;j<n;++j){
            cin>>a[i][j];
            --a[i][j];
        }
    ll res=0;
    int top=0,bot=0;
    for(int i=0;i<n;++i){
        top+=a[0][i];
        bot+=a[1][i];
        if((top<0 and bot>0) or (top>0 and bot<0)){
            if(abs(top)<abs(bot)){
                res+=abs(top);
                bot+=top;
                top=0;
            }else{
                res+=abs(bot);
                top+=bot;
                bot=0;
            }
        }
        res+=abs(top+bot);
    }
    cout<<res<<'\n';
}
