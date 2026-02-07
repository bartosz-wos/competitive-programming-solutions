#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int pref[26][50005];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    int q;
    cin>>s>>q;
    for(int i=1;i<=(int)s.size();++i){
        for(int j=0;j<26;++j)
            pref[j][i]=pref[j][i-1];
        ++pref[s[i-1]-97][i];
    }
    while(q--){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        bool ok=1;
        for(int i=0;i<26;++i)
            if(pref[i][b]-pref[i][a-1]!=pref[i][d]-pref[i][c-1]){
                ok=0;
                break;
            }
        if(ok)cout<<"DA\n";
        else cout<<"NE\n";
    }
}
