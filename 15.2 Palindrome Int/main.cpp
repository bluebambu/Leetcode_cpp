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
        /*����pow������ʱ��������⣬��Ϊ�и����������pow����ǿ��
        ȡ���Ļ����ܻ���ֽϴ�������pow(10, 2)���ܵ���99.9999��ȡ��
        ����99, ���Խ���취��д��(int)(pow(10, 2) + .5)�������뻹��
        ����lz��ֻ�õ��������������ݵ����������Լ�д���˷���������Ϊ
        ��������¿⺯���ٶȲ����ÿ죬���һ��в���Ҫ�����*/

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
        if(x<0) return isPalindrome(-x);  // ����������false��

        int d=1, tmp=x;

        while(x/d>=10){
            d*=10;
        }

        while(tmp){ // ��������Ҳ����д�� d >= 10
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
