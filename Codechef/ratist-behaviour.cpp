#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll tt;
    tt=1;
    cin>>tt;
    while(tt--){          
        ll n;
        cin>>n;
        ll a[n];
        ll ans=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        string s;
        cin>>s;
        map <pair<ll,ll>,ll> m; 
        for(int i=0;i<n;i++){
            m[{-1*a[i],s[i]-'0'}]++;
        }
        ll cnt=0;
        ll total=0;
        multiset <ll> ms;
        ll x;
        for(auto it:m){
            ans=max(it.second,ans);
            if(it.first.second==0){
                total+=it.second;
                cnt+=it.second;
                ans=max(ans,total);
            }else{  
                if(cnt!=0){
                    cnt--;
                    total+=it.second;
                    ans=max(ans,total);
                    ms.insert(it.second);
                    if(cnt==0){
                        cnt++;
                        x=*ms.begin();total-=x;
                        ms.erase(ms.begin());
                    }
                }
            }
        }
        cout<<ans<<"\n";
    }
	return 0;
}
