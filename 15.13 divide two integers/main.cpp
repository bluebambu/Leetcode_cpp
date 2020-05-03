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

    ///////////Leetcode passed////////////////////////
    int divide(int dividend, int divisor) {
        if(divisor==0) return INT_MAX;
        bool sign=(dividend ^ divisor)>>31; // false = +, true = - ;

        long long a = dividend >0 ? dividend : ((long long)(dividend) * -1);
        long long b = divisor >0 ? divisor : ((long long)(divisor) * -1);

        long long result=0;
        int i=31;  //  这个 31 很重要， 32 貌似就不行，还不知道为什么

        cout<<a<<" "<<b<<endl;
        while(i>=0){
            long long tmp = (long long)(b<<i);
            //cout<<tmp<<"   ";
            if(tmp > a) {--i; continue;}
            else{
                result+=(long(1)<<i);
                a-=tmp;
                --i;
                cout<<result;
            }
            //cout<<result;
        }
        return (sign? -result : result)>INT_MAX ? INT_MAX : (sign? -result : result);  // INT_MIN * -1 == INT_MAX, 但 INT_MAX 绝对值比 int min 少1， 无语。。。。。。。。。。 和 compiler 相关。
    }


    ///////////////////////// leetcode passed   更加方便一些！！！   /////////////////////////
    int divide2(int dividend, int divisor) {
        if(divisor==0) return INT_MAX;
        bool sign=(dividend ^ divisor)>>31; // false = +, true = - ;

        long long a = dividend >0 ? dividend : ((long long)(dividend) * -1);
        long long b = divisor >0 ? divisor : ((long long)(divisor) * -1);

        long result=0;
        int i=31;

        //cout<<a<<" "<<b<<endl;
        while(i>=0){
            long long tmp=a>>i;
            if(tmp>=b){
                a-=(b<<i);
                result+=((long long)(1)<<i); // 此处的long 必不可少！！！！！ 要注意！！！ 然而codeblock的compiler有问题，即便 long long 也对(-2147483648,-1) 还是得不到正确结果.........
                //cout<<endl<<result;
            }
            i--;
            // cout<<endl<<tmp;
        }

        return (sign? -result : result)>INT_MAX ? INT_MAX : (sign? -result : result);
    }
};

int main()
{
    Solution a;


    cout<<a.divide2(-2147483648,-1);


}
