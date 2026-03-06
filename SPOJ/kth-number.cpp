#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct node{
	int v=0;
	node*l=nullptr,*r=nullptr;
	node(){}
	node(int x):v(x){}
	node(node*ll,node*rr){
		l=ll;
		r=rr;
		v=0;
		if(l)v+=l->v;
		if(r)v+=r->v;
	}
	node(node*x){
		v=x->v;
		l=x->l;
		r=x->r;
	}
};
 
int n,q;
node*roots[100002];
map<int,int>mp,inv;
 
node*build(int l=1, int r=mp.size()){
	if(l==r)return new node(0);
	int mid=(l+r)>>1;
	return new node(build(l,mid),build(mid+1,r));
}
 
node*upd(node*t,int i,int l=1,int r=mp.size()){
	if(l==r)return new node(t->v+1);
	int mid=(l+r)>>1;
	if(i<=mid)return new node(upd(t->l,i,l,mid),t->r);
	else return new node(t->l,upd(t->r,i,mid+1,r));
}
 
int L,R,K;
int get(node*t1,node*t2){
	int l=1,r=mp.size(),mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(t2->l->v-t1->l->v<K){
			K-=t2->l->v-t1->l->v;
			t1=t1->r;
			t2=t2->r;
			l=mid+1;
		}else{
			t1=t1->l;
			t2=t2->l;
			r=mid;
		}
	}
	return l;
}
 
void solve(){
	cin>>L>>R>>K;
	--L;
	int res=get(roots[L],roots[R]);
	cout<<inv[res]<<'\n';
}
 
int a[100001];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int cnt=1;
	cin>>n>>q;
	priority_queue<int,vector<int>,greater<int>>Q;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		Q.push(a[i]);
	}
	for(int i=1;i<=n;++i){
		int x=Q.top();
		Q.pop();
		if(!mp[x]){
			mp[x]=cnt++;
			inv[cnt-1]=x;
		}
	}
	roots[0]=build();
	for(int i=1;i<=n;++i)
		roots[i]=upd(roots[i-1],mp[a[i]]);
	while(q--)solve();
}
