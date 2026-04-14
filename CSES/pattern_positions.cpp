#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
vector<int>T(1e6,1e6);
 
void build(int k, int l, int r, const vector<int>&SA){
	if(l==r){
		T[k]=SA[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid,SA);
	build(k<<1|1,mid+1,r,SA);
	T[k]=min(T[k<<1],T[k<<1|1]);
}
 
int query(int ql, int qr, int k, int l, int r){
	if(l>qr or r<ql)
		return 1e6;
	if(ql<=l and r<=qr)
		return T[k];
	int mid=(l+r)>>1;
	return min(query(ql,qr,k<<1,l,mid),query(ql,qr,k<<1|1,mid+1,r));
}
 
vector<int> SCS(const string&s){
	int n=s.size();
	const int alphabet=256;
 
	vector<int>p(n),c(n),cnt(max(alphabet,n),0);
 
	for(int i=0;i<n;++i)
		++cnt[s[i]];
	for(int i=1;i<alphabet;++i)
		cnt[i]+=cnt[i-1];
	for(int i=0;i<n;++i)
		p[--cnt[s[i]]]=i;
	c[p[0]]=0;
	int classes=1;
	for(int i=1;i<n;++i){
		if(s[p[i]]!=s[p[i-1]])
			++classes;
		c[p[i]]=classes-1;
	}
 
	vector<int>pn(n),cn(n);
 
	for(int h=0;(1<<h)<n;++h){
		for(int i=0;i<n;++i){
			pn[i]=p[i]-(1<<h);
			if(pn[i]<0)
				pn[i]+=n;
		}
		fill(cnt.begin(),cnt.begin()+classes,0);
		for(int i=0;i<n;++i)
			++cnt[c[pn[i]]];
		for(int i=1;i<classes;++i)
			cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;--i)
			p[--cnt[c[pn[i]]]]=pn[i];
		classes=1;
		cn[p[0]]=0;
		for(int i=1;i<n;++i){
			pair<int,int>cur={c[p[i]],c[(p[i]+(1<<h))%n]};
			pair<int,int>prev={c[p[i-1]],c[(p[i-1]+(1<<h))%n]};
			if(cur!=prev)
				++classes;
			cn[p[i]]=classes-1;
		}
		c.swap(cn);
	}
	return p;
}
 
vector<int> SA_build(string s){
	s+='$';
	vector<int>p=SCS(s);
	p.erase(p.begin());
	return p;
}
 
int check(const string&s, const string&p, const int&pos){
	int f=1;
	if(s.size()-pos>=p.size())
		f=0;
	for(int i=0;i<min(p.size(),s.size()-pos);++i){
		if(s[pos+i]<p[i])
			return 1;
		else if(s[pos+i]>p[i])
			return -1;
	}
	return f;
}
 
void solve(const string&s, const vector<int>&SA){
	string p;
	cin>>p;
 
	int l=0,r=s.size()-1,mid=0;
	int res1,res2;
	res1=res2=-1;
	while(l<=r){
		mid=(l+r)>>1;
		int c=check(s,p,SA[mid]);
		if(c==0){
			res1=mid;
			r=mid-1;
		}
		else if(c==-1)
			r=mid-1;
		else
			l=mid+1;
	}
	if(res1==-1){
		cout<<-1<<'\n';
		return;
	}
	l=0,r=s.size()-1;
	while(l<=r){
		mid=(l+r)>>1;
		int c=check(s,p,SA[mid]);
		if(c==0){
			res2=mid;
			l=mid+1;
		}
		else if(c==-1)
			r=mid-1;
		else
			l=mid+1;
	}
	cout<<query(res1,res2,1,0,s.size()-1)+1<<'\n';
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string s;
	cin>>s;
	vector<int>SA=SA_build(s);
	build(1,0,s.size()-1,SA);
	int q;
	cin>>q;
	while(q--)
		solve(s,SA);
}
