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

        /// bool sign = ~ ( (a>0) ^ (b>0) );  ���ﲻ��д�� ���� ��Ϊ����ζ�� sign = bool( ~(...)) ,
        /// ������һ����Ϊ���int��NOT ����֮�� ��Ȼ��Ϊ�㣬����sign��ȻΪ 1. ���� ~(00001) = 111110
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
    //���������ɳ˷��Ĺ������ƣ����μ��������x�����ģ�y^(2^31),y^(2^30),...y^8,y^4,y^2,y^1��������Ӧ������y���ڽ��������Ӧ��������
    int Pos_Div(int x,int y)
    {
        int ans=0;
        for(int i=31;i>=0;i--)
        {
            //�Ƚ�x�Ƿ����y��(1<<i)�η������⽫x��(y<<i)�Ƚϣ���Ϊ��ȷ��y��(1<<i)�η��Ƿ����
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
        ���ʵ�ַ������ã� n^2 �ĸ��Ӷȡ� Ӧ�ô� a ��ʼλ�ơ�
        */

        for(int i=31; i>=0; --i){
            if( (a>>i) >= b ){  /// ע��˴�Ӧ����  >= ������ > , ��Ϊ  a/a = 1 ��
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
