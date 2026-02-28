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

struct Poly{
	ll mod=998244353;
	ll c=119;
	ll root=-1;
	ll root_1=-1;
	ll root_pw=1<<23;
	vector<int>p;
	Poly(){}
	Poly(int n){p.assign(n,0);}
	Poly(vector<int> p):p(p){}
	void trim(){while(!p.empty() and !p.back())p.pop_back();}
	int size()const{return p.size();}
	void resize(int n){p.resize(n);}
	bool empty()const{return p.empty();}
	int& operator[](int i){return p[i];}
	const int& operator[](int i)const{return p[i];}

	Poly& operator+=(const Poly&b){
		if(size()<b.size())resize(b.size());
		for(int i=0;i<b.size();++i){
			p[i]+=b[i];
			if(p[i]>=mod)p[i]-=mod;
		}
		return *this;
	}
	Poly operator+(const Poly&b)const{return Poly(*this)+=b;}

	Poly& operator-=(const Poly&b){
		if(size()<b.size())resize(b.size());
		for(int i=0;i<b.size();++i){
			p[i]-=b[i];
			if(p[i]<0)p[i]+=mod;
		}
		return *this;
	}
	Poly operator-(const Poly&b)const{return Poly(*this)-=b;}

	Poly operator*(const Poly&b){
		if(empty() or b.empty())return Poly();
		vector<int>res=conv((*this).p,b.p);
		return Poly(res);
	}
	Poly& operator*=(const Poly&b){
		return *this = (*this)*b;
	}

	void fft(vector<int>&a, bool f){
        	int n=a.size();
        	for(int i=1,j=0;i<n;++i){
                	int b=n>>1;
                	for(;j&b;b>>=1)j^=b;
                	j^=b;
                	if(i<j)swap(a[i],a[j]);
        	}

        	for(int len=2;len<=n;len<<=1){
                	int wlen = exp(f?root_1:root,root_pw/len,mod);
                	for(int i=0;i<n;i+=len){
                  	      int w=1;
                        	for(int j=0;j*2<len;++j){
                                	int u=a[i+j], v=(int)(1ll*a[i+j+len/2]*w%mod);
                                	a[i+j]=u+v<mod?u+v:u+v-mod;
                                	a[i+j+len/2]=u-v>=0?u-v:u-v+mod;
                                	w=(int)(1ll*w*wlen%mod);
                        	}
                	}
        	}
        	if(f){
                	int n1=exp(n,mod-2,mod);
                	for(int&x:a)
                  	      x=(int)(1ll*x*n1%mod);
        	}
	}

	vector<int>mult(const vector<int>&a, const vector<int>&b){
        	vector<int>a2(a.begin(),a.end()),b2(b.begin(),b.end());
        	int n=1;
        	while(n<a.size()+b.size())n<<=1;
        	a2.resize(n);
        	b2.resize(n);
        	fft(a2,0);
        	fft(b2,0);
        	for(int i=0;i<n;++i)
                	a2[i]=(int)(1ll*a2[i]*b2[i]%mod);
        	fft(a2,1);
        	return a2;
	}

	vector<int>conv(const vector<int>&a, const vector<int>&b){
        	if(!~root){
                	root=exp(p_root(mod),c,mod);
                	root_1=exp(root,mod-2,mod);
        	}
        	vector<int>res=mult(a,b);
        	int n=a.size()+b.size();
        	while(res.size()>=n)res.pop_back();
        	return res;
	}

	Poly deriv()const{
		if(empty())return Poly();
		Poly res(size()-1);
		for(int i=1;i<size();++i)
			res[i-1]=(int)(1ll*(*this)[i]*i%mod);
		return res;
	}

	Poly integr()const{
		if(empty())return Poly();
		Poly res(size()+1);
		res[0]=0;
		for(int i=0;i<size();++i){
			int inv=exp(i+1,mod-2,mod);
			res[i+1]=(int)(1ll*(*this)[i]*inv%mod);
		}
		return res;
	}

	Poly inv(int n)const{
		if(p.empty() or p[0]==0)return Poly();
		Poly res(1);
		res[0]=exp(p[0],mod-2,mod);
		int len=1;
		while(len<n){
			len<<=1;
			Poly a(len);
			for(int i=0;i<min(size(),len);++i)a[i]=p[i];
			Poly p2=a*res;
			p2.resize(len);
			Poly two(len);
			two[0]=2;
			res=res*(two-p2);
			res.resize(len);
		}
		res.resize(n);
		return res;
	}

	Poly ln(int n)const{
		if(empty() or p[0]!=1)return Poly();
		Poly res=deriv()*inv(n);
		res.resize(n-1);
		res=res.integr();
		res.resize(n);
		return res;
	}

	Poly poly_exp(int n)const{
		if(empty()){
			Poly res(1);
			res[0]=1;
			return res;
		}
		if(p[0]!=0)return Poly();
		Poly res(1);
		res[0]=1;
		int len=1;
		while(len<n){
			len<<=1;
			Poly log=res.ln(len);
			Poly p2(len);
			for(int i=0;i<min(size(),len);++i)
				p2[i]=p[i];
			Poly one(1);
			one[0]=1;
			res=res*(one-log+p2);
			res.resize(len);
		}
		res.resize(n);
		return res;
	}

	Poly pow(ll k, int n)const{
		if(!k){
			Poly res(1);
			res[0]=1;
			res.resize(n);
			return res;
		}
		int off=0;
		while(off<size() && !p[off])++off;
		if(off == size() or (off>0 and k>=n/off+1)){
			return Poly(n);
		}
		int new_n=n-off*k;
		Poly p2(new_n);
		ll inv_v0=exp(p[off],mod-2,mod);
		ll v0_k=exp(p[off],k%(mod-1),mod);
		for(int i=0;i<new_n and i+off<size();++i)
			p2[i]=(int)(1ll*p[i+off]*inv_v0%mod);
		Poly res=p2.ln(new_n);
		for(int i=0;i<new_n;++i)
			res[i]=(int)(1ll*res[i]*(k%mod)%mod);
		res=res.poly_exp(new_n);
		Poly ret(n);
		int st=(int)(off*k);
		for(int i=0;i<new_n && i+st<n;++i)
			ret[i+st]=(int)(1ll*res[i]*v0_k%mod);
		return ret;
	}

	friend istream& operator>>(istream&is, Poly&p){
		for(int i=0;i<p.size();++i)is>>p[i];
		return is;
	}
	friend ostream& operator<<(ostream&os, const Poly&p){
		for(int i=0;i<p.size();++i)
			os<<p[i]<<' ';
		return os;
	}
};


int main(){
	ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        init();
	int n;
	ll m;
	cin>>n>>m;
	Poly a(n);
	cin>>a;
	cout<<a.pow(m,n)<<'\n';
}
