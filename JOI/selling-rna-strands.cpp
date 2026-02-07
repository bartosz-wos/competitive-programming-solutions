#include <bits/stdc++.h>
using namespace std;
int n,m;
int getNum(char f) {
  if(f=='A') return 0;
  if(f=='U') return 1;
  if(f=='G') return 2;
  return 3;
}
char getChar(int x) {
  if(x==0) return 'A';
  if(x==1) return 'U';
  if(x==2) return 'G';
  return 'C';
}
struct Trie {
  struct node {
    node* child[4];
    int l,r;
    int exist;
    node() {
      for(int i=0;i<4;i++) child[i]=NULL;
      l=INT_MAX,r=INT_MIN;
      exist=0;
    }
  };
  node* root;
  Trie() {
    root = new node();
  }
  void add(string s,int id) {
    node* u =root;
    for(char c : s) {
      int temp=getNum(c);
      if(u->child[temp]==NULL) u->child[temp]= new node();
      u=u->child[temp];
      u->l=min(u->l,id);
      u->r=max(u->r,id);
    }
    u->exist++;
  }
  pair<int,int> find(string s) {
    node* u = root;
    for(char c: s) {
      int temp=getNum(c);
      if(u->child[temp]==NULL) return {-1,-1};
      u=u->child[temp];
    }
    return {u->l,u->r};
  }
  void sortString(node* u,string cur,vector<string>& v) {
    for(int i=0;i<u->exist;i++) v.push_back(cur);
    for(int i=0;i<4;i++) if(u->child[i]!=NULL) {
      cur+=getChar(i);
      sortString(u->child[i],cur,v);
      cur.pop_back();
    }
  }
};
struct Trie2{
  struct node {
    node* child[4];
    vector<int> id;
    node() {
      for(int i=0;i<4;i++) child[i]=NULL;
    }
  };
  node* root;
  Trie2() {
    root=new node();
  }
  void add(string s,int idx) {
    node* u=root;
    reverse(s.begin(),s.end());
    for(char c:s) {
      int temp=getNum(c);
      if(u->child[temp]==NULL) u->child[temp]=new node();
      u=u->child[temp];
      u->id.push_back(idx);
    }
  }
  int solve(string s,pair<int,int> idx) {
    node* u=root;
    reverse(s.begin(),s.end());
    for(char c:s) {
      int temp=getNum(c);
      if(u->child[temp]==NULL) return 0;
      u=u->child[temp];
    }
    int l=lower_bound(u->id.begin(),u->id.end(),idx.first)-u->id.begin();
    int r=upper_bound(u->id.begin(),u->id.end(),idx.second)-u->id.begin();
    return r-l;
  }
};
void sort(vector<string> &v) {
  Trie trie;
  for(string s: v) trie.add(s,-1);
  vector<string>().swap(v);
  trie.sortString(trie.root,"",v);
}
int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    vector<string> v;
    for(int i=0;i<n;i++) {
      string x;cin>>x;
      v.push_back(x);
    }
    sort(v);
    Trie trie;
    Trie2 trie2;
    for(int i=0;i<n;i++) {
      trie.add(v[i],i);
      trie2.add(v[i],i);
    }
    while(m--) {
      string head,tail;cin>>head>>tail;
      pair<int,int> idx=trie.find(head);
      if(idx.first==-1) cout << 0 << '\n';
      else cout << trie2.solve(tail,idx) << '\n';
    }
    return 0;
}
