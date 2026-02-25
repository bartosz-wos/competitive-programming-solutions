#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pt=array<ll,3>;

__int128 abs(__int128 x){
	return x<0?-x:x;
}

__int128 sq(ll x){
        return (__int128)x*x;
}

int sgn(__int128 x){
        return (x>0)-(x<0);
}

__int128 orient_v(const pt&a, const pt&b, const pt&c){
        return (__int128)a[0]*(b[1]-c[1])+(__int128)b[0]*(c[1]-a[1])+(__int128)c[0]*(a[1]-b[1]);
}

ll orient(const pt&a, const pt&b, const pt&c){
	return sgn(orient_v(a,b,c));
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
        if(s.size()==2 and s[0][0]==s[1][0] and s[0][1]==s[1][1])s.pop_back();
        a=s;
}

__int128 dist(const pt&a, const pt&b){
        return sq(a[0]-b[0])+sq(a[1]-b[1]);
}

int mod(int x, int y, int m){
        x+=y;
        if(x<0)x+=m;
        if(x>=m)x-=m;
	return x;
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
		for(int i=0;i<n;++i){
			cin>>a[i][0]>>a[i][1];
			a[i][2]=i;
		}
                sort(a.begin(),a.end(),[](const pt&a, const pt&b){
			if(a[0]!=b[0])return a[0]<b[0];
			return a[1]<b[1];		
		});
                a.erase(unique(a.begin(),a.end(),[](const pt&a, const pt&b){
			return a[0]==b[0] and a[1]==b[1];			
		}),a.end());
                if(a.size()>1)hull(a);
                __int128 d=0;
                pt res={0,1,-1};
		n=a.size();
                for(int i=0,j=1;i<n;++i){
			int nxt=mod(i,1,n);
			while(abs(orient_v(a[i],a[nxt],a[mod(j,1,n)]))>abs(orient_v(a[i],a[nxt],a[j])))j=mod(j,1,n);
                        if(dist(a[i],a[j])>d){
                                d=dist(a[i],a[j]);
                                res={a[i][2],a[j][2]};
                        }
			if(dist(a[nxt],a[j])>d){
				d=dist(a[nxt],a[j]);
				res={a[nxt][2],a[j][2]};
			}
                }
                cout<<res[0]<<' '<<res[1]<<'\n';
        }
}
