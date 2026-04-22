#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
bool ask(int a, int b){
    cout<<"? "<<a<<' '<<b<<endl;
    string s;
    cin>>s;
    if(s=="YES")return 1;
    return 0;
}
 
int main(){
    int n;
    cin>>n;
    vector<int>a(n);
    iota(a.begin(),a.end(),1);
    stable_sort(a.begin(),a.end(),ask);
    vector<int>ret(n);
    for(int i=0;i<n;++i)
        ret[a[i]-1]=i+1;
    cout<<"! ";
    for(const int&i:ret)cout<<i<<' ';
}
