#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pt=array<ll,2>;

ll sq(ll x){
        return x*x;
}

int sgn(ll x){
        return (x>0)-(x<0);
}

int orient(const pt&a, const pt&b, const pt&c){
        ll x=a[0]*(b[1]-c[1])+b[0]*(c[1]-a[1])+c[0]*(a[1]-b[1]);
        return sgn(x);
}

void hull(vector<pt>&a){
        int idx=min_element(a.begin(),a.end(),[&](const pt&a, const pt&b){
                if(a[1]==b[1])return a[0]<b[0];
                return a[1]<b[1];
        })-a.begin();
        swap(a[0],a[idx]);
        pt p0=a[0];
        sort(a.begin()+1,a.end(),[&](const pt&a, const pt&b){
                int x=orient(p0,a,b);
                if(!x)return sq(p0[0]-a[0])+sq(p0[1]-a[1])<sq(p0[0]-b[0])+sq(p0[1]-b[1]);
                return x>0;
        });
        vector<pt>s;
        for(int i=0;i<a.size();++i){
                while(s.size()>1 and orient(s[s.size()-2],s.back(),a[i])<=0)
                        s.pop_back();
                s.push_back(a[i]);
        }
        if(s.size()==2 and s[0]==s[1])s.pop_back();
        a=s;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        int t;
        cin>>t;
        while(t--){
                int n;
                cin>>n;
                vector<pt>a(n);
                for(auto&[x,y]:a)cin>>x>>y;
                sort(a.begin(),a.end());
                a.erase(unique(a.begin(),a.end()),a.end());
                if(a.size()>1)hull(a);
                cout<<a.size()<<'\n';
                for(const auto&[x,y]:a)
                        cout<<x<<' '<<y<<'\n';
        }
}
