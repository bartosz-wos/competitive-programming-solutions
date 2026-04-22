#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct node{
    node*c[2];
}*root;
 
int n,sum;
 
void upd(int x){
    node *cur=root;
    for(int i=30;i>=0;--i){
        if(x&(1<<i)){
            if(!cur->c[1])cur->c[1]=new node();
            cur=cur->c[1];
        }
        else{
            if(!cur->c[0])cur->c[0]=new node();
            cur=cur->c[0];
        }
    }
}
 
int ask(int x){
    int res=0;
    node *cur=root;
    for(int i=30;i>=0;--i){
        if(x&(1<<i)){
            if(cur->c[0]){
                res+=(1<<i);
                cur=cur->c[0];
            }
            else
                cur=cur->c[1];
        }
        else{
            if(cur->c[1]){
                res+=(1<<i);
                cur=cur->c[1];
            }
            else
                cur=cur->c[0];
        }
    }
    return res;
}
 
int res;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    root=new node();
    upd(0);
    cin>>n;
    for(int i=0,x;i<n;++i){
        cin>>x;
        sum^=x;
        upd(sum);
        res=max(res,ask(sum));
    }
    cout<<res<<'\n';
}

