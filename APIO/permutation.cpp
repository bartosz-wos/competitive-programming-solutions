#include<bits/stdc++.h>
#include "perm.h"
#define int long long
using namespace std;
vector<int32_t> szukaj(long long x)
{
    if(x<=1)
        return {};
    if(x==2)
        return {0};
    for(long long i=3;i<=7;i+=2)
    {
        if(x%i==0 && x!=i)
        {
            vector<int32_t> mam1=szukaj(i);
            vector<int32_t> mam2=szukaj(x/i);
            for(int i=0;i<mam2.size();i++)
                mam1.push_back(mam2[i]+mam1.size()-i);
            return mam1;
        }
    }
    vector<int32_t> mam=szukaj(x/2);
    mam.push_back(mam.size());
    if(x%2==1)
        mam.insert(mam.begin(),mam.size());
    return mam;
}
vector<int32_t> construct_permutation(long long x)
{
    return szukaj(x);
}
