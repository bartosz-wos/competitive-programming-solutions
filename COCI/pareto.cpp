#include <bits/stdc++.h>
#define int long long
#define db long double

using namespace std;

signed main() {
  int n=0;
  int a=0;
  db b=0;
  db c=0;
  db d=0;
  int i=0;
  
  cin>>n;
  vector<int> vec(n);
  vector<pair<db, db>> veco(n);
  
  for(i=0;i<n;i++) {
    cin>>a;
    vec.at(i) = a;
    
    c += a;
  }
  
  sort(vec.begin(), vec.end());
  reverse(vec.begin(), vec.end());
  
  a=0;
  b=0;
  
  for(i=0;i<n;i++) {
    b = (i+1);
    b *= 100;
    b /= n;
    
    veco.at(i).first = b;
  }
  
  a=0;
  b=0;
  
  for(i=0;i<n;i++) {
      b += vec.at(i);
      d = b;
      
      d *= 100;
      d /= c;
      
      veco.at(i).second = d;
  }
  
  b=0;
  
  for(i=0;i<n;i++) {
      if((veco.at(i).second - veco.at(i).first) > b) {
          b = (veco.at(i).second - veco.at(i).first);
          a = i;
      }
  }
  
  cout<<setprecision(50);
  cout<<veco.at(a).first<<endl;
  
  cout<<setprecision(50);
  cout<<veco.at(a).second<<endl;
  
  return 0;
}
