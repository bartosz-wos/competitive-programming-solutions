#include "encoder.h"
#include "encoderlib.h"
#include <bits/stdc++.h>

using namespace std;

int bits = 4;
int emp = 64 / pow(2, 8 - bits);
int pn = 5; 

map<int, map<int, long long>> dp;

long long f(int num, int niv) {
  if (niv == 0) return 1;
  if (niv == 1 || num == 0) {
    return num;
  }
  if (dp[num][niv] == 0) {
    dp[num][niv] = f(num, niv - 1) + f(num - 1, niv);
  }
  return dp[num][niv];
}

void sendcode(long long code, int niv, int pre, vector<pair<long long, long long>> &posi) {
  for (int t1 = niv; t1 >= 1; t1 --) {
    for (int t2 = (1<<bits)-1; t2 >= 0; t2 --) {
      if (code >= f(t2, t1)) {
        send(pre + t2);
        code -= f(t2, t1);
        break ;
      }
    }
  }
}

void empac(long long code, int pre, vector<pair<long long, long long>> &posi) {
  for (int niv = 1; niv < posi.size(); niv ++) {
    if (posi[niv].first <= code && code <= posi[niv].second) {
      code -= posi[niv].first;
      sendcode(code, niv, pre << bits, posi);
      break ;
    }
  }
}

void encode(int n, int m[]) {
  vector<pair<long long, long long>> posi = {{-1, -1}};
  for (int t1 = 1; t1 <= emp*pn; t1 ++) {
    posi.push_back({f((1<<bits)+1, t1 - 1) - 1, f((1<<bits)+1, t1 - 1) + f((1<<bits), t1) - 2});
  }
  int sup = (1<<(8-bits)) - 1;
  int index = 0;
  while (n >= emp) {
    long long code = 0;
    for (int t1 = 0; t1 < emp; t1 ++) {
      code <<= 8;
      code += m[index];
      index ++;
    }
    empac(code, sup, posi);
    n -= emp;
    sup --;
  }
  if (n != 0) {
    long long code = 0;
    for (int t1 = 0; t1 < n; t1 ++) {
      code <<= 8;
      code += m[index];
      index ++;
    }
    empac(code, sup, posi);
    sup --;
  }
  return ;
}

