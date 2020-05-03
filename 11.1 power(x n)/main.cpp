#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution
{
public:
    double pow(double x, int n)
    {
        if(n<0) return 1.0/pow(x, -n);
        else return power(x,n);
    }

    double power(double x, int n)
    {
        if(n==0) return 1;
        double v=power(x, n/2);
        if(n%2==0) return v*v;
        else return v*v*x;
    }

//////////////////////////////////////////
    double myPow(double x, int n) {
        // power(x, n) = x(n/2) * x(n/2) * x(n%2)
        if(n== -1) return 1/x; // 必需的，处理 n<0 的情况
        if(n==0) return 1;
        if(n==1) return x;
        double v=myPow(x, n/2);
        return v*v*myPow(x,n%2);
    }

///////////////////////////////////////////
    double myPow(double x, int n) {
        if(n==0) return 1;
        if(n==1) return x;
        if(n==-1) return 1/x;

        double half = myPow(x, n/2);

        if(n%2 != 0 )
            return half*half*myPow(x, n%2);
        else
            return half*half;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    double b = a.power2(8, 3);
            cout<<b<<" ";

    cout<<endl;

}
