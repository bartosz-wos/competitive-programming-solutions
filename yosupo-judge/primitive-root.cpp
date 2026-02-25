#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using lll=__int128;

ll exp(ll a, ll w, ll m){
        a%=m;
        ll res=1;
        while(w){
                if(w&1)res=(lll)res*a%m;
                a=(lll)a*a%m;
                w>>=1;
        }
        return res;
}

bool not_comp(ll n, ll a, ll d, ll s){
        ll x=exp(a,d,n);
        if(x==1 or x==n-1)return 0;
        for(int i=1;i<s;++i){
                x=(lll)x*x%n;
                if(x==n-1)return 0;
        }
        return 1;
}

vector<int>pr;

bool prime(ll n){
        if(n<=5)return n==2 or n==3 or n==5;
        ll s=0;
        ll d=n-1;
        while(~d&1){
                ++s;
                d>>=1;
        }
        for(const int&i:pr){
		if(i>37)break;
                if(n==i)return 1;
                if(not_comp(n,i,d,s))return 0;
        }
        return 1;
}

ll pollard_single(ll n) {
	if(prime(n))return n;
    	if(~n&1)return 2;
    	ll st=0;
    	auto f=[&](ll x){return ((lll)x*x+st)%n;};
    	while(1){
        	++st;
        	ll x=f(st),y=f(x);
        	while(1){
        	    ll p=gcd(abs(y-x),n);
        	    if (!p or p==n)break;
        	    if (p^1)return p;
        	    x=f(x);
        	    y=f(f(y));
        	}
    	}
}

int s[10000005];

void init(){
	for(int i=2;i<=(ll)1e7;++i){
                if(!s[i]){
                        s[i]=i;
                        pr.push_back(i);
                }
                for(int j=0;pr[j]*i<=(ll)1e7;++j){
                        s[pr[j]*i]=pr[j];
                        if(pr[j]==s[i])break;
                }
        }
}

vector<ll>fact(ll n){
        vector<ll>ret;
        while(s[n]!=n and n!=1){
                ret.push_back(s[n]);
                n/=s[n];
        }
        if(n!=1)ret.push_back(n);
        return ret;
}

vector<ll>get(ll n) {
    if(n==1)return {};
    if(n<=(ll)1e7)return fact(n);
    ll x=pollard_single(n);
    if(x==n)return {x};
    vector<ll>f1=get(x);
    vector<ll>f2=get(n / x);
    f1.insert(f1.end(),f2.begin(),f2.end());
    return f1;
}

ll p_root(ll n){
	if(n==2)return 1;
	ll p=n-1;
	vector<ll>f=get(p);
	for(ll i=2;i<=n;++i){
		bool ok=1;
		for(const ll&x:f)
			if(!(exp(i,p/x,n)^1)){
				ok=0;
				break;
			}
		if(ok)return i;
	}
	return -1;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    	init();
    	int q;
    	cin>>q;
	while(q--){
		ll n;
		cin>>n;
		cout<<p_root(n)<<'\n';
	}
}

