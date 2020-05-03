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

    int dp[50]={0};

    int climbStairs1(int n)
    {
        if(n==1) return 1;
        if(n==2) return 2;

        dp[n] = climbStairs1(n-2)+climbStairs1(n-1);
        return dp[n];
    }

    int climbStairs2(int n)
    {
        int t1=1,t2=2;
        int t3;

        for(int i=3;i<=n;++i)
        {
            t3=t1+t2;
            t1=t2;
            t2=t3;
        }
        return t3;
    }

//////////////////// leetcode passed //////////////////////////
    int climbStairs(int n) {
        if(n<3) return n;
        int first=1, second=2, third=0;
        int idx=0;

        while(idx!=n-2){
            third=first+second;
            first=second;
            second=third;
            idx++;
        }

        return third;
    }
};

int main()
{
    Solution a;
    int b[] = {1,3,5,7,9};
    int c[] = {2,4, 6, 8,10};
    vector<int> d {1,299,54,2,645,4,6,3};

    auto len_final = a.climbStairs2(8);
    cout<<"result = "<<len_final<<endl;


}
