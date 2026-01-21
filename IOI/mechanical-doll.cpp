#include "bits/stdc++.h"
#include "doll.h"
//#define int long long
#define all(v) v.begin() , v.end()
#define sz(a) (int)a.size()
using namespace std;

const int INF = (int) 1e9;
vector<int> x,y,state,hm;
int p=1,p2=0;

void give_index(int rt,int l,int r){
  int mid = (l+r)/2;
  if(r-l==1){
    if(mid+1>sz(hm)) x[rt]=-1;
    return;
  }
  if(mid+1>sz(hm)) x[rt]=-1;
  else{
    x[rt]=-(++p);
    x.push_back(-INF);
    y.push_back(-INF);
    state.push_back(0);
    give_index(-x[rt],mid+1,r);
  }
  y[rt]=-(++p);
  x.push_back(-INF);
  y.push_back(-INF);
  state.push_back(0);
  give_index(-y[rt],l,mid);
}
 
void make_leaf(int rt){
  if(state[rt]==0){
    state[rt]^=1;
    if(x[rt]==-INF) x[rt]=hm[p2++];
    else make_leaf(-x[rt]);
  }
  else{
    state[rt]^=1;
    if(y[rt]==-INF) y[rt]=hm[p2++];
    else make_leaf(-y[rt]);
  }
}

void create_circuit(int m, vector<int> a){
  vector<int> c(m+1);
  
  x.push_back(-INF);
  y.push_back(-INF);
  state.push_back(0);


  a.push_back(0);
  x.push_back(-INF);
  y.push_back(-INF);
  state.push_back(0);

  hm=a;
  for(int i=0;i<=m;i++) c[i]=-1;
   
  int nd=1;
  while(nd<sz(hm)) nd<<=1;

  give_index(1,1,nd);
  for(int i=0;i<sz(hm);i++) make_leaf(1);


  reverse(all(x));
  x.pop_back();
  reverse(all(x));

  reverse(all(y));
  y.pop_back();
  reverse(all(y));

  answer(c, x, y);
}
