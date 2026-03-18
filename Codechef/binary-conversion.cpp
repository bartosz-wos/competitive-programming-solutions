#include <bits/stdc++.h>
#define int long long int
#define pb push_back
#define fore(i, a, b) for (int i = a; i < b; i++)
using namespace std;

bool isprime(int n)
{
    if (n == 1)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;

    int zeros=0, ones=0, zerot=0, onest=0;
    for(auto x: s){
        if(x=='1')ones++;
        else zeros++;
    }
    for(auto x: t){
        if(x=='1')onest++;
        else zerot++;
    }

    if(ones==onest and zeros==zerot){
        int ct=0;
        for(int i=0; i<n; i++){
            if(s[i]!=t[i]){
                ct++;
            }
        }

        if(n==2){
            if(s=="00" and t=="00") cout<<"YES\n";
            else if(s=="11" and t=="11") cout<<"YES\n";
            
            else if(s=="01" and t=="10" and k==2) cout<<"NO\n";
            else if(s=="10" and t=="01" and k==2) cout<<"NO\n";
            else if(s=="01" and t=="01" and k==1) cout<<"NO\n";
            else if(s=="10" and t=="10" and k==1) cout<<"NO\n";
            else cout<<"YES\n";
        }
        else if((ct/2)<=k) cout<<"YES\n";
        else cout<<"NO\n";
    }
    else cout<<"NO\n";

}

signed main()
{
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
