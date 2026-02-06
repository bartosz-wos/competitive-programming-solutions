#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N = 30,INF=1e12;
string a,b;
int n;
int32_t main()
{
  //freopen("abc.in", "r", stdin);
  cin>>n;
  cin>>a>>b;
  int aa=0,bb=0,cc=0,aaa=0,bbb=0,ccc=0;
  string ans="";
  for(int i = 0 ; i < a.size() ; i++)
  {
    if(a[i]=='a') aa++;
    else if(a[i]=='b') bb++;
    else cc++;

    if(b[i]=='a') aaa++;
    else if(b[i]=='b') bbb++;
    else ccc++;
  }

  for(int i = 0 ; i < n ; i ++){
    if(b[i]=='a' && (bb-1+aa)>=(ccc) && (bb-1+cc)>=(aaa-1) && bb) ans+='b',aaa--,bb--;
    else if(b[i]=='a') ans+='c',aaa--,cc--;
    else if(b[i]=='c' && (aa-1+cc)>=(bbb) && (aa-1+bb)>=(ccc-1) && aa) ans+='a',ccc--,aa--;
    else if(b[i]=='c') ans+='b',ccc--,bb--;
    else if(b[i]=='b' && (aa-1+bb)>=(ccc) && (aa-1+cc)>=(bbb-1) && aa) ans+='a',bbb--,aa--;
    else if(b[i]=='b') ans+='c',bbb--,cc--;
  }
  cout<<ans;
}
