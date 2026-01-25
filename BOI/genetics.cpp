#include<bits/stdc++.h>
using namespace std;
using ll=long long;

ll n,m,k;

string s[5005];

ll cnt[5005][4];
int cv(char c){
    if(c=='A')return 0;
    else if(c=='C')return 1;
    else if(c=='G')return 2;
    return 3;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>k;
    srand(time(nullptr));
    vector<int>v(n+1,0);
    ll sv=0;
    for(int i=1;i<=n;++i){
        cin>>s[i];
        v[i]=rand()%((int)1e9);
        for(int j=0;j<m;++j){
            int c=cv(s[i][j]);
            cnt[j][c]+=v[i];
        }
        sv+=v[i];
    }
    vector<int>ch;
    for(int i=1;i<=n;++i){
        ll ss=0;
        for(int j=0;j<m;++j){
            int c=cv(s[i][j]);
            for(int k=0;k<=3;++k)
                if(k!=c)
                    ss+=cnt[j][k];
        }
        if(ss==k*(sv-v[i]))ch.push_back(i);
    }
    cout<<ch[0]<<'\n';
}
