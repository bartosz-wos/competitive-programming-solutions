#include <iostream>
using namespace std;

#define int long long

struct struct_aint{
    int sum,pref_min,pref_max;
};

struct_aint v[400005];

struct_aint combin(struct_aint a,struct_aint b){
    struct_aint rasp;
    rasp.pref_min=min(a.pref_min,a.sum+b.pref_min);
    rasp.pref_max=max(a.pref_max,a.sum+b.pref_max);
    rasp.sum=a.sum+b.sum;
    return rasp;
}

void update(int nod,int st,int dr,int poz,int a){
    if(st==dr){
        v[nod].sum=a;
        v[nod].pref_min=a;
        v[nod].pref_max=a;
        return ;
    }
    int mij=(st+dr)/2;
    if(mij>=poz) update(2*nod,st,mij,poz,a);
    else update(2*nod+1,mij+1,dr,poz,a);
    v[nod]=combin(v[2*nod],v[2*nod+1]);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,i,poz,a;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a>>poz;
        if(poz==1) update(1,1,n,n-a+1,-1);
        else update(1,1,n,n-a+1,1);
        if(v[1].pref_max<=0) cout<<">\n";
        else if(v[1].pref_min>=0) cout<<"<\n";
        else cout<<"?\n";
    }
    return 0;
}

