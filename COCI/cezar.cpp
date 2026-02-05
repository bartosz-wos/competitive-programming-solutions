#include <bits/stdc++.h>
#define int long long
#define ff first
#define ss second
#define pb push_back
#define all(x) x.begin(),x.end()
using namespace std;
signed main(){
    ios_base::sync_with_stdio();
    cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector <int> cnt(12);
    for(int i=1;i<=11;i++){
        cnt[i]=4;
    }
    cnt[10]*=4;
    int sum=0;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        sum+=x;
        cnt[x]--;
    }
    int d=21-sum;
    int cnt1=0,cnt2=0;
    for(int i=1;i<=11;i++){
        if(i>d)cnt1+=cnt[i];
        else cnt2+=cnt[i];
    }
    if(cnt1<cnt2)cout<<"VUCI\n";
    else cout<<"DOSTA\n";
}


