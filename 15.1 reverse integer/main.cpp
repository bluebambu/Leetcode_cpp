#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    string reverse(long long x){
        if(x<0) return "-"+reverse(-x);
        string r;

        for(;x!=0;x/=10){
            if(r.size()==0 && x%10 ==0)
                continue;
            else
                r+='0'+x%10;
        }

        return r;
    }


    //////////// pass leetcode //////////////////
    int reverse2(int x) {// 用long来处理overflow的情况

        long int result=0;


        while(x){
            result = result*10+x%10;
            x=x/10;
        }

        if(result>INT_MAX||result<INT_MIN) return 0;

        return result;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.reverse(230002342434234);
    cout<<b;
}
