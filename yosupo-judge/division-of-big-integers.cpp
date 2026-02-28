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

ll mod_sqrt(ll a, ll m){
	if(exp(a,(m-1)/2,m)!=1)return a==0?0:-1;
	if(m%4==3)return exp(a,(m+1)/4,m);
	ll s=0,d=m-1;
	while(~d&1)d>>=1,++s;
	ll n=2;
	while(exp(n,(m-1)/2,m)!=m-1)++n;
	ll res=exp(a,(d+1)/2,m);
	ll c=exp(n,d,m);
	ll t=exp(a,d,m);
	ll val=s;
	while(t!=1){
		ll i=1,temp=t*t%m;
		while(temp!=1)temp=temp*temp%m,++i;
		ll b=exp(c,1ll<<(val-i-1),m);
		val=i;
		c=b*b%m;
		t=t*c%m;
		res=res*b%m;
	}
	return min(res,m-res);
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
	Poly rev()const{
		Poly res=*this;
		reverse(res.p.begin(),res.p.end());
		return res;
	}
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

	Poly operator/(const Poly&b)const{
		if(size()<b.size())return Poly();
		int qlen=size()-b.size()+1;
		Poly a_rev=rev();
		Poly b_rev=b.rev();
		b_rev.resize(qlen);
		Poly inv=b_rev.inv(qlen);
		Poly q_rev=a_rev*inv;
		q_rev.resize(qlen);
		return q_rev.rev();
	}

	Poly& operator/=(const Poly&b){
		return *this = (*this)/b;
	}

	Poly operator%(const Poly&b)const{
		if(size()<b.size())return *this;
		Poly q=(*this)/b;
		Poly r=(*this)-q*b;
		r.resize(b.size()-1);
		r.trim();
		return r;
	}

	Poly operator%=(const Poly&b){
		return *this=(*this)%b;
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

	Poly poly_sqrt(int n)const{
		if(n<=0)return Poly();
		int k=0;
		while(k<size() and !p[k])++k;
		if(k==size())return Poly(n);
		if(k&1)return Poly();
		ll r0=mod_sqrt(p[k],mod);
		if(r0==-1)return Poly();
		int off=k/2;
		if(off>=n)return Poly(n);
		int new_n=n-off;
		Poly p2(new_n);
		ll inv_v0=exp(p[k],mod-2,mod);
		for(int i=0;i<new_n and i+k<size();++i)
			p2[i]=(int)(1ll*p[i+k]*inv_v0%mod);
		Poly res(1);
		res[0]=1;
		ll inv2=(mod+1)>>1;
		int len=1;
		while(len<new_n){
			len<<=1;
			Poly p3(min((int)p2.size(),len));
			for(int i=0;i<p3.size();++i)
				p3[i]=p2[i];
			res=(res+p3*res.inv(len));
			for(int i=0;i<res.size();++i)
				res[i]=(int)(1ll*res[i]*inv2%mod);
			res.resize(len);
		}
		Poly ret(n);
		for(int i=0;i<new_n and i+off<n;++i)
			ret[i+off]=(int)(1ll*res[i]*r0%mod);
		return ret;
	}

	Poly composition(const Poly&g, int n)const{
		int B=sqrt(n)+1;
		vector<Poly>small(B+1);
		small[0]=Poly(1);
		small[0][0]=1;
		for(int i=1;i<=B;++i){
			small[i]=small[i-1]*g;
			small[i].resize(n);
		}
		vector<Poly>q;
		for(int i=0;i*B<n;++i){
			Poly q2(n);
			for(int j=0;j<B and i*B+j<n and i*B+j<size();++j){
				int c=p[i*B+j];
				for(int k=0;k<small[j].size();++k)
					q2[k]=(q2[k]+1ll*c*small[j][k])%mod;
			}
			q.push_back(q2);
		}
		Poly res(n);
		Poly p2=small[B];
		for(int i=q.size()-1;i>=0;--i){
			if(i==q.size()-1)
				res=q[i];
			else{
				res=res*p2;
				res.resize(n);
				res=res+q[i];
			}
		}
		res.resize(n);
		return res;
	}

	Poly compositional_inv(int n)const{
		if(n<=1)return Poly(n);
		Poly g(2);
		g[0]=0;
		g[1]=exp(p[1],mod-2,mod);
		Poly d=deriv();
		int len=1;
		while(len<n){
			len<<=1;
			int len2=len<<1;
			Poly fg=composition(g,len2);
			Poly p2=fg;
			p2.resize(len2);
			if(p2.size()>1)p2[1]=(p2[1]-1+mod)%mod;
			else{
				p2.resize(2);
				p2[1]=mod-1;
			}
			Poly dfg=d.composition(g,len2);
			g=g-(p2*dfg.inv(len2));
			g.resize(len2);
		}
		g.resize(n);
		return g;
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

void big_norm(vector<int>&a){
	ll c=0;
	for(int i=0;i<a.size() or c;++i){
		if (i==a.size())a.push_back(0);
		ll cur=a[i]+c;
		c=cur/10;
		a[i]=cur%10;
	}
	while(!a.empty() and !a.back())a.pop_back();
}

int big_cmp(const vector<int>&a,const vector<int>&b){
	if(a.size()!=b.size())return a.size()>b.size()?1:-1;
	for(int i=a.size()-1;i>=0;--i) {
		if(a[i]!=b[i])return a[i]>b[i]?1:-1;
	}
	return 0;
}

vector<int>shift_left(const vector<int>&a,int k){
	if(a.empty())return {};
	vector<int>res(a.size()+k);
	for(int i=0;i<a.size();++i)res[i+k]=a[i];
	return res;
}

vector<int>shift_right(const vector<int>&a,int k){
	if(a.size()<=k)return {};
	return vector<int>(a.begin()+k,a.end());
}

vector<int>big_add(vector<int>a, const vector<int>&b){
	int c=0;
	for(int i=0; i<max(a.size(),b.size()) or c;++i){
		if(i==a.size())a.push_back(0);
		a[i]+=(i<b.size()?b[i]:0)+c;
		if(a[i]>=10){a[i]-=10;c=1;}
		else c=0;
	}
	while(!a.empty() and !a.back())a.pop_back();
	return a;
}

vector<int>big_sub(vector<int>a,const vector<int>&b){
	int c=0;
	for(int i=0;i<a.size();++i){
		int sub=(i<b.size()?b[i]:0)+c;
		if(a[i]<sub){a[i]+=10-sub;c=1;}
		else{a[i]-=sub;c=0;}
	}
	while(!a.empty() and !a.back())a.pop_back();
	return a;
}

vector<int>big_mul(const vector<int>&a, const vector<int>&b){
	if (a.empty() or b.empty())return {};
	Poly pa(a),pb(b);
	Poly pc=pa*pb;
	vector<int>res=pc.p;
	big_norm(res);
	return res;
}

vector<int>big_inv(const vector<int>&a){
	int n=a.size();
	if (n<=2) {
		ll val=0;
		for(int i=n-1;i>=0;--i)val=val*10+a[i];
		lll num=1;
		for(int i=0;i<2*n;++i)num*=10;
		lll q=num/val;
		vector<int>res;
		while(q){res.push_back(q%10);q/=10;}
		return res;
	}
	int k=(n+1)/2;
	vector<int>a_high=shift_right(a,n-k);
	vector<int>z_prime=big_inv(a_high);
	vector<int>term1(n+k+1,0);
	term1.back()=2;
	vector<int>term2=big_mul(a,z_prime);
	vector<int>term3=big_sub(term1,term2);
	vector<int> res=shift_right(big_mul(z_prime,term3),2*k);
	return res;
}

pair<vector<int>,vector<int>>big_div_mod(const vector<int>&a,const vector<int>&b){
	if(big_cmp(a,b)<0)return {{},a};
	int m=b.size();
	if(m<=2){
		ll b_val=0;
		for(int i=m-1;i>=0;--i)b_val=b_val*10+b[i];
		vector<int>q(a.size());
		ll rem=0;
		for(int i=a.size()-1;i>=0;--i){
			rem=rem*10+a[i];
			q[i]=rem/b_val;
			rem%=b_val;
		}
		while(!q.empty() and !q.back())q.pop_back();
		vector<int>r;
		while(rem){r.push_back(rem%10);rem/=10;}
		return {q,r};
	}
	vector<int>z=big_inv(b);
	vector<int>q=shift_right(big_mul(a,z),2*m);
	vector<int>r=big_sub(a,big_mul(q,b));
	vector<int>one={1};
	while(big_cmp(r,b)>=0) {
		r=big_sub(r,b);
		q=big_add(q,one);
	}
	return {q,r};
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	init();
	int t;
	cin>>t;
	while(t--){
		string a,b;
		cin>>a>>b;
		if(a=="0"){
			cout<<"0 0\n";
			continue;
		}
		vector<int>pa(a.size()),pb(b.size());
		for(int i=0;i<a.size();++i)
			pa[i]=a[i]-48;
		for(int i=0;i<b.size();++i)
			pb[i]=b[i]-48;
		reverse(pa.begin(),pa.end());
		reverse(pb.begin(),pb.end());
		auto[q,r]=big_div_mod(pa,pb);
		if(q.empty())cout<<0;
		else{
			reverse(q.begin(),q.end());
			for(int i=0;i<q.size();++i)
				cout<<q[i];
		}
		cout<<' ';
		if(r.empty())cout<<0;
		else{
			reverse(r.begin(),r.end());
			for(int i=0;i<r.size();++i)
				cout<<r[i];
		}
		cout<<'\n';
	}
}
