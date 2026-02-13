#include <bits/stdc++.h>
using namespace std;
#define int long long
#define faster ios_base::sync_with_stdio(false);cin.tie(NULL);
#define OYY 1000000005
#define mod 998244353
int l[100000],r[100000],u[100000],d[100000];

int32_t main(){
    faster
    int n;cin>>n;
    for(int i=0;i<n;i++){
        cin>>l[i];
    }
    for(int i=0;i<n;i++){
        cin>>r[i];
    }
    for(int i=0;i<n;i++){
        cin>>u[i];
    }
    for(int i=0;i<n;i++){
        cin>>d[i];
    }
//////////////////////////////////////
    bool stop=true;
    for(int i=0;i<n && stop;i++){
        //cout<<l[i]<<" "<<r[i]<<endl;
        if(l[i]==-1 && r[i]==-1)continue;
        if(l[i]==-1 || r[i]==-1){
             //   cout<<"y"<<endl;
            stop=0;
            break;
        }
        if(l[i]+r[i]<n)continue;
        stop=0;
        break;
    }
    //cout<<stop<<endl;
    for(int i=0;i<n && stop;i++){
        if(u[i]==-1 && d[i]==-1)continue;
        if(u[i]==-1 || d[i]==-1){
            stop=0;break;
        }
        if(u[i]+d[i]<n)continue;
        stop=0;
        break;
    }
    if(stop)cout<<"DA"<<'\n';
    else cout<<"NE"<<'\n';
    return 0;
}
