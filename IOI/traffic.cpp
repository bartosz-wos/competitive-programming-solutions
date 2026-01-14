#include<bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int>g[1000001];
int n,opt,a[1000001];
ll res=1e18,sum;

ll f(int v, int e){
        ll mv=0;
        ll s=0;
        for(const int&i:g[v])
                if(i!=e){
                        ll t=f(i,v);
                        s+=t;
                        mv=max(mv,t);
                }
        s+=a[v];
        mv=max(mv,sum-s);
        if(res>mv){
                res=mv;
                opt=v;
        }
        return s;
}

int LocateCentre(int N, int pp[], int S[], int D[]){
        n=N;
        for(int i=0;i<n;++i){
                a[i]=pp[i];
                sum+=a[i];
        }
        for(int i=1;i<n;++i){
                g[S[i-1]].push_back(D[i-1]);
                g[D[i-1]].push_back(S[i-1]);
        }
        f(0,-1);
        return opt;
}

