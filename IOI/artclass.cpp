

    #include "artclass.h"
    #include <bits/stdc++.h>
    int style(int H,int W,int R[500][500],int G[500][500],int B[500][500])
    {
        long long ans = 0;
        for(int x=0;x<H;x++)
            for(int y=0;y<W-1;y++)
            {
                int RR=abs(R[x][y]-R[x][y+1]);
                int GG=abs(G[x][y]-G[x][y+1]);
                int BB=abs(B[x][y]-B[x][y+1]);
                ans+=(RR+GG+BB);
            }
        ans/=(H*(W-1));
        if(ans<=8) return 4;
        if(ans<=25) return 1;
        if(ans<=53) return 2;
       	return 3;
    }
