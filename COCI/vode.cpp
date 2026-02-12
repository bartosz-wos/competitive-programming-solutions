#include <bits/stdc++.h>

#define f first
#define s second
#define m_p make_pair
#define vec vector
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define sz(x) (int)(x).size()
#define fast_izho ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define pw(x) (1<<(x))
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("-O3")
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
template <class T> bool umax(T &a,const T &b){return (a<b?a=b,1:0);}
template <class T> bool umin(T &a,const T &b){return (a>b?a=b,1:0);}
const int N=5001;
bool dp[N][N];
signed main(){
    fast_izho;
    int n,m,k;
    cin>>n>>m>>k;
    vec<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
//        for(int j=m;j>m-k;j--)
//            dp[i][j]=1;
    }
    vec<int> cnt(n);///of ones
    for(int j=m-1;j>=0;j--){
        for(int i=0;i<n;i++){
            int nx=(i+1)%n;
            int lo=(cnt[nx]<k?1:0),wi=(cnt[nx]>0?1:0);
            dp[i][j]=(a[i]==a[nx]?wi:lo);
//            cnt[i]+=dp[i][j];
//            cout<<"WIN "<<i<<' '<<j<<' '<<dp[i][j]<<endl;
//            cout<<"A "<<dp[i][j]<<' '<<cnt[i]<<endl;
        }
        for(int i=0;i<n;i++)
            cnt[i]+=dp[i][j],cnt[i]-=dp[i][j+k];

    }
    for(int i=0;i<n;i++){
        cout<<(a[i]^dp[i][1]^1)<<' ';
    }
    return 0;
}
