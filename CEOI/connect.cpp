#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second 
#define all(a) a.begin(),a.end()
#define pii pair <int,int>
#define PII pair<pii , pii>
#define sz(v) (int)v.size()
#define rep(i , a , b) for(int i=a;i <= (b);i++)
#define per(i , a , b) for(int i=a;i >= (b);i--)
using namespace std ;   
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int maxn = 2e6 + 10 , inf= 1e4, mod = 998244353;
int n, m;
char a[2*13+1][2*39+10];
int how[13][39];
int memo[13][39][1<<13][2];
 
const char *b[3][11] = {
   { "+ +", "+ +", "+.+", "+ +", "+ +", "+ +", "+.+", "+.+", "+.+", "+ +", "+ +" },
   { "   ", ".X ", " X ", " X.", " X ", "...", " . ", ".. ", " ..", " ..", ".. " },
   { "+ +", "+ +", "+ +", "+ +", "+.+", "+ +", "+.+", "+ +", "+ +", "+.+", "+.+" },
};
 
int rec( int r, int c, int mask, int U, int reconstruct ) {
   if( r == n ) return rec( 0, c+1, mask, 0, reconstruct );
   if( c == m ) return 0;
 
   int &ret = memo[r][c][mask][U];
   if( !reconstruct && ret >= 0 ) return ret;
 
   ret = inf;
 
   int L = (mask>>r)&1;
   int R = a[2*r+1][2*c+2] == ' ';
   int D = a[2*r+2][2*c+1] == ' ';
   int X = a[2*r+1][2*c+1] == 'X';
 
   int h0=0, h1=0, h2=0, h3=0;
 
   #define tst(t0,t1,t2,t3) { \
      int v = t1 + rec( r+1, c, t2, t3, 0 ); \
      if( v < ret ) { ret = v; h0=t0; h1=t1; h2=t2; h3=t3; } \
   }
 
   if( !X && !L && !U && 1 && 1 ) tst(  0, 0, mask & ~(1<<r), 0 ); // empty
 
   if(  X &&  L && !U && 1 && 1 ) tst(  1, 1, mask & ~(1<<r), 0 ); // left
   if(  X && !L &&  U && 1 && 1 ) tst(  2, 1, mask & ~(1<<r), 0 ); // up
   if(  X && !L && !U && R && 1 ) tst(  3, 1, mask |  (1<<r), 0 ); // right
   if(  X && !L && !U && 1 && D ) tst(  4, 1, mask & ~(1<<r), 1 ); // down
 
   if( !X &&  L && !U && R && 1 ) tst(  5, 2, mask |  (1<<r), 0 ); // left-right
   if( !X && !L &&  U && 1 && D ) tst(  6, 2, mask & ~(1<<r), 1 ); // up-down
 
   if( !X &&  L &&  U && 1 && 1 ) tst(  7, 2, mask & ~(1<<r), 0 ); // left-up
   if( !X && !L &&  U && R && 1 ) tst(  8, 2, mask |  (1<<r), 0 ); // up-right
   if( !X && !L && !U && R && D ) tst(  9, 2, mask |  (1<<r), 1 ); // right-down
   if( !X &&  L && !U && 1 && D ) tst( 10, 2, mask & ~(1<<r), 1 ); // down-left
 
   if( reconstruct ) {
      how[r][c] = h0;
      rec( r+1, c, h2, h3, 1 );
   }
 
   return ret;
}
 
int main( void ) {
   scanf( "%d%d ", &n, &m );
   for( int r = 0; r < n; ++r ) {
     fgets( a[r], 90, stdin );
     int l = strlen(a[r]);
     while(a[r][l-1] == '\r' || a[r][l-1] == '\n') a[r][l-1] = 0;
   }
   n /= 2; m /= 2;
 
   memset( memo, -1, sizeof memo );
   printf( "%d\n", rec( 0, 0, 0, 0, 1 ) );
 
   for( int r = 0; r < n; ++r )
      for( int c = 0; c < m; ++c )
         for( int dr = 0; dr < 3; ++dr )
            for( int dc = 0; dc < 3; ++dc )
               if( b[dr][how[r][c]][dc] != ' ' )
                  a[2*r+dr][2*c+dc] = b[dr][how[r][c]][dc];
 
   for( int r = 0; r <= 2*n; ++r ) puts( a[r] );
   return 0;
}
