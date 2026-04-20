#include<bits/stdc++.h>
using namespace std;
using ll=long long;
mt19937 rng(time(nullptr));
struct nod{
	char v;
	ll p;
	int sz;
	bool rev;
	nod*l,*r;
	nod(char c){
		v=c;
		p=rng();
		sz=1;
		rev=0;
		l=r=nullptr;
	}
};
int cnt(nod*t){return t?t->sz:0;}
void pull(nod*t){if(t)t->sz=1+cnt(t->l)+cnt(t->r);}
void push(nod*t){
	if(t and t->rev){
		t->rev=0;
		swap(t->l,t->r);
		if(t->l)t->l->rev^=1;
		if(t->r)t->r->rev^=1;
	}
}
void split(nod*t,nod*&l,nod*&r,int key){
	if(!t)return void(l=r=nullptr);
	push(t);
	if(key<=cnt(t->l))split(t->l,l,t->l,key),r=t;
	else split(t->r,t->r,r,key-cnt(t->l)-1),l=t;
	pull(t);
}
void mer(nod*&t,nod*l,nod*r){
	push(l);push(r);
	if(!l or !r)t=l?l:r;
	else if(l->p > r->p)mer(l->r,l->r,r),t=l;
	else mer(r->l,l,r->l),t=r;
	pull(t);
}
void reverse(nod*t,int l, int r){
	nod*a,*b,*c;
	split(t,a,b,l-1);
	split(b,b,c,r-l+1);
	b->rev^=1;
	mer(t,a,b);
	mer(t,t,c);
}
void print(nod*t){
	if(!t)return;
	push(t);
	print(t->l);
	cout<<t->v;
	print(t->r);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	string s;
	nod*t=nullptr;
	cin>>n>>q>>s;
	for(const char&c:s)mer(t,t,new nod(c));
	while(q--){
		int l,r;
		cin>>l>>r;
		reverse(t,l,r);
	}
	print(t);
}
