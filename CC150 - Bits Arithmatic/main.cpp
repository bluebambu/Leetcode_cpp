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
    int add(int a, int b){
        if(b==0)
            return a;
        if(a<b)
            return add(b,a);

        int sum = a^b,
            carry = a&b;
        return add(sum, carry<<1);
    }

    int minus(int a, int b){
        return add(a, -b);
    }

    int multiply(int a, int b){
        if(a==0 || b==0) return 0;

        /// bool sign = ~ ( (a>0) ^ (b>0) );  这里不能写成 ～， 因为这意味着 sign = bool( ~(...)) ,
        /// 而任意一个不为零的int在NOT 操作之后， 依然不为零，所以sign依然为 1. 比如 ~(00001) = 111110
        bool sign = ! ( (a>0) ^ (b>0) );

        a = abs(a), b=abs(b);
        int result=0;

        for(int i=0; i<32; ++i){
            if(b & (1<<i)){
                result = add(result, a<<i);
            }
        }

        return sign ? result : ( (~result) + 1);

    }
    /**
    //除法就是由乘法的过程逆推，依次减掉（如果x够减的）y^(2^31),y^(2^30),...y^8,y^4,y^2,y^1。减掉相应数量的y就在结果加上相应的数量。
    int Pos_Div(int x,int y)
    {
        int ans=0;
        for(int i=31;i>=0;i--)
        {
            //比较x是否大于y的(1<<i)次方，避免将x与(y<<i)比较，因为不确定y的(1<<i)次方是否溢出
            if((x>>i)>=y)
            {
                ans+=(1<<i);
                x-=(y<<i);
            }
        }
        return ans;
    }
    */

    int divide(int a, int b){
        if(a==0) return 0;
        bool sign = ! ( (a>0) ^ (b>0) );

        a = abs(a), b=abs(b);
        int result=0;

        /**
        while(a>=0){
            int i=0;
            for(; b<<i < a; ++i);
            a = minus(a, b<<(i-1));
            if(a>=0) result = add(result, 1<<(i-1));
        }
        这个实现方法不好， n^2 的复杂度。 应该从 a 开始位移。
        */

        for(int i=31; i>=0; --i){
            if( (a>>i) >= b ){  /// 注意此处应该是  >= 而不是 > , 因为  a/a = 1 ；
                result = add(result, 1<<i);
                a = minus(a, b<<i);
            }
        }

        return sign ? result : add(~result, 1);
    }

    int neg(int a){
        if(a<0)
            return a;
        else
            return ~(a)+1;
    }

    int pos(int a){
        if(a>0) return a;
        else return ~(a-1);
    }

};

int main()
{
    Solution a;

    cout<<a.divide(77, -7);




}
