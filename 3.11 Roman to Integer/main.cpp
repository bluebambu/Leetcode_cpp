#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    int RomanToint(string str)
    {
        int result=0;

        for(auto i=str.begin(); i<str.end();++i)
        {
            switch(*i)
            {
            case 'M':
                result+=1000;
                break;
            case 'D':
                result+=500;
                break;
            case 'C':
                if(*(i+1)=='M')
                    {result+=900;++i;}
                else if(*(i+1)=='D')
                    {result+=400;++i;}
                else
                    result+=100;
                break;
            case 'L':
                result+=50;
                break;
            case 'X':
                if(*(i+1)=='C')
                    {result+=90;++i;}
                else if(*(i+1)=='L')
                    {result+=40;++i;}
                else
                    result+=10;
                break;
            case 'V':
                result+=5;
                break;
            case 'I':
                if(*(i+1)=='X')
                    {result+=9;++i;}
                else if(*(i+1)=='V')
                    {result+=4;++i;}
                else
                    result+=1;
                break;

            }
        }

        return result;
    }

    int map(const char c){
        switch(c){
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }

    int RomanToint2(string str){
        int result =0;
        for(int i=0; i<str.size(); ++i){
            if(i>0 && map(str[i])>map(str[i-1])){
                result += (map(str[i])) - 2*map(str[i-1]);
            } else {
                result += map(str[i]);
            }
        }

        return result;
    }

};

int main()
{
    Solution a;
    string b("MCMLXXXIV");

    auto c=a.RomanToint(b);
//    for(auto i=0;i<a.size();++i)
        cout<<c;

}
