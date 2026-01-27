#include "grader.h"
#include "cluedo.h"
#include <bits/stdc++.h>

using namespace std;

void Solve(){
    int mur=1, loc=1, wea=1;
    while(mur<=6 and loc<=10 and wea<=6){
        int q=Theory(mur, loc, wea);
        if(q==1){
            mur++;
        }
        else if(q==2){
            loc++;
        }
        else{
            wea++;
        }
    }
}

