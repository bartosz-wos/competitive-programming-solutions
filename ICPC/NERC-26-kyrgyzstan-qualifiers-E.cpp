#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        int n;
        ll k;
        cin>>n>>k;

        int l=1,r=n;

        while(l<=r){
                ll rem=r-l;
                if(k>=rem){
                        cout<<r<<' ';
                        k-=rem;
                        --r;
                }else{
                        int t=l+k;
                        cout<<t<<' ';
                        for(int i=l;i<=r;++i)
                                if(i!=t)
                                        cout<<i<<' ';
                        break;
                }
        }
        cout<<'\n';
}
