#include<bits/stdc++.h>
#include "combo.h"
using namespace std;
string tmp="ABXY";
char first_char () {
    int tmp1 = press("AB");
    if(tmp1) {
        if(press("A") == 1) {
            tmp.erase(tmp.begin());
            return 'A';
        } else {
            tmp.erase(tmp.begin()+1);
            return 'B';
        }
    } else {
        if(press("X") == 1) {
            tmp.erase(tmp.begin()+2);
            return 'X';
        } else {
            tmp.erase(tmp.begin()+3);
            return 'Y';
        }
    }
}

char last_char(string s, string tmp, int n) {
    if(press(s + tmp[0]) == n) return tmp[0]; else 
    if(press(s + tmp[1]) == n) return tmp[1]; else
    return tmp[2];
}

string guess_sequence(int N) {
    string s = "";
    char c_first = first_char();
    s += c_first;
    while(s.size() < N - 1) {
        string z=s + tmp[0] + tmp[0] + s + tmp[0] + tmp[1] + s + tmp[0] + tmp[2] + s + tmp[1];
        int t = press(z);
        if(t == s.size() + 2) {
            s = s + tmp[0];
        } else 
        if(t == s.size() + 1) {
            s = s + tmp[1];
        } else {
            s = s + tmp[2];
        }
    }
    if (N<=1) return s;
    char c_last = last_char(s, tmp, N);
    s += c_last;
    return s;
}
