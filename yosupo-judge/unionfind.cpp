#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct dsu{
        vector<int>p;
        dsu(int n){
                p.resize(n+1,-1);
        }
        int fd(int x){
                return p[x]<0?x:p[x]=fd(p[x]);
        }
        bool unite(int a, int b){
                a=fd(a);
                b=fd(b);
                if(a==b)return 0;
                p[b]+=p[a];
                p[a]=b;
                return 1;
        }
};

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int n,q;
        cin>>n>>q;
        dsu g(n);
        while(q--){
                int t,a,b;
                cin>>t>>a>>b;
                if(!t)g.unite(a,b);
                else cout<<(g.fd(a)==g.fd(b))<<'\n';
        }
}
