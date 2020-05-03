// _template.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <map>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }

class solution {
public:
    bool isMatch(string s, string t){
        return mch(s, 0, t, 0);
    }
    bool mch(string s, int scur, string t, int tcur){
        int sstar=-1, tstar=-1;

        while(scur<s.size()){
            if( s[scur]== t[tcur] || t[tcur]=='?')
                ++scur, ++tcur;
            else if(t[tcur]=='*'){
                tstar=tcur, tcur+=1;
            }else if(tstar!=-1){
                tcur=tstar+1;
                sstar+=1;
                scur=sstar;
            }else
                return false;
        }
        while(tcur<t.size() && t[tcur]=='*')
            ++tcur;
        return tcur==t.size();
    }
};


int main()
{
    string s="kjadjf";
    for(int i=0; i<100; ++i)
        cout<<*(s.end()+i)<<"#";

}
