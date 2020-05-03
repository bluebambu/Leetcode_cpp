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
    bool isPalindrome(int x) { // int((pow(10, size-1))) = 9999990 !!!
        /*是用pow函数的时候出了问题，因为有浮点误差，如果对pow函数强行
        取整的话可能会出现较大误差。例如pow(10, 2)可能等于99.9999，取整
        后变成99, 所以解决办法是写成(int)(pow(10, 2) + .5)四舍五入还有
        建议lz在只用到整数的整数次幂的情况下最好自己写个乘方函数，因为
        这种情况下库函数速度不见得快，而且还有不必要的误差*/

        if(x<0) return isPalindrome(-x);

        int size=0, tmp=x;

        while(tmp){
            tmp/=10;
            size++;
        }

        tmp=x;

        for(int i=1; size>1;){
            int left = tmp/pow(10, size-1);
            int right = tmp%10;

            if(left!=right) return false;

            tmp=tmp%int((pow(10, size-1)));
            // int((pow(10, size-1))) = 9999990 !!!
            tmp/=10;
            size-=2;
        }

        return true;
    }

    bool isPalindrome2(int x) {
        if(x<0) return isPalindrome(-x);  // 负数可以是false；

        int d=1, tmp=x;

        while(x/d>=10){
            d*=10;
        }

        while(tmp){ // 这里条件也可以写成 d >= 10
            int left = tmp/d;
            int right = tmp%10;

            if(left != right) return false;

            tmp%=d;
            tmp/=10;
            d/=100;
        }
        return true;
    }
};


int main()
{
    Solution a;

    vector<int> intset {1,2,3};

    auto b = a.isPalindrome2(10000021);


    cout<<b<<" ";


}
