#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;
using vi=vector<int>;

#define fi first
#define se second

constexpr int N=3e5+5;
constexpr int A=2500+5;
constexpr int inf=1e9;

int n;
int posr[N],posc[N];
int s[A][A];
int rmin[N],rmax[N];
int cmin[N],cmax[N];
ll s1[A][A],s2[A][A];

int get(int a, int b, int c, int d){
    return s[c][d]-s[a-1][d]-s[c][b-1]+s[a-1][b-1];
}

pi next1(pi cur){
    int r=cur.fi,c=cur.se;
    return {min(r,rmin[c-1]),max(c,cmax[r+1])};
}

pi next2(pi cur){
    int r=cur.fi,c=cur.se;
    return {max(r,rmax[c+1]),min(c,cmin[r-1])};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for(int i=0;i<N;++i)
        rmin[i]=cmin[i]=inf;
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>posr[i]>>posc[i];
        ++s[posr[i]][posc[i]];
        rmin[posc[i]]=min(rmin[posc[i]], posr[i]);
        cmax[posr[i]]=max(cmax[posr[i]], posc[i]);
        rmax[posc[i]]=max(rmax[posc[i]], posr[i]);
        cmin[posr[i]]=min(cmin[posr[i]], posc[i]);
    }
    for(int i=1;i<A;++i){
        rmin[i]=min(rmin[i-1],rmin[i]);
        cmin[i]=min(cmin[i-1],cmin[i]);
    }
    for(int i=A-2;i>=0;--i){
        rmax[i]=max(rmax[i+1],rmax[i]);
        cmax[i]=max(cmax[i+1],cmax[i]);
    }
    for(int i=1;i<A;++i)
        for(int j=1;j<A;++j)
            s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
    for(int r=0;r<A;++r)
        for(int c=A-1;c>=0;--c){
            pi it=next1({r,c});
            s1[r][c]=get(1,c,r,A-1)+s1[it.fi][it.se];
        }
    for(int r=A-1;r>=0;--r)
        for(int c=0;c<A;++c){
            pi it=next2({r,c});
            s2[r][c]=get(r,1,A-1,c)+s2[it.fi][it.se];
        }
    for(int i=1;i<=n;++i)
        cout<<n-3+s1[posr[i]][posc[i]]+s2[posr[i]][posc[i]]<<'\n';
}
